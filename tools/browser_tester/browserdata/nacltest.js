// Copyright (c) 2011 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


function $(id) {
  return document.getElementById(id);
}


function exceptionToLogText(e) {
  if (typeof e == 'object' && 'message' in e && 'stack' in e) {
    return e.message + '\n' + e.stack.toString();
  } else if (typeof(e) == 'string') {
    return e;
  } else {
    return toString(e)
  }
}


// Logs test results to the server using URL-encoded RPC.
// Also logs the same test results locally into the DOM.
function RPCWrapper() {
  // Workaround how JS binds 'this'
  var this_ = this;
  // It is assumed RPC will work unless proven otherwise.
  this.rpc_available = true;
  // Set to true if any test fails.
  this.ever_failed = false;
  // Async calls can make it faster, but it can also change order of events.
  this.async = false;

  // Called if URL-encoded RPC gets a 404, can't find the server, etc.
  function handleRPCFailure(name, message) {
    // This isn't treated as a testing error - the test can be run without a
    // web server that understands RPC.
    this_.logLocal('RPC failure for ' + name + ': ' + message + ' - If you ' +
                   'are running this test manually, this is not a problem.',
                   'gray');
    this_.disableRPC();
  }

  function handleRPCResponse(name, req) {
    if (req.status == 200) {
      // URL-encoded RPC always responds 'OK'.  If we get anything else, worry.
      if (req.responseText != 'OK') {
        this_.logLocal('Unexpected RPC response to ' + name + ': \'' +
                       req.responseText + '\' - If you are running this test ' +
                       'manually, this is not a problem.', 'gray');
        this_.disableRPC();
      }
    } else {
      handleRPCFailure(name, req.status.toString());
    }
  }

  // Performs a URL-encoded RPC call, given a function name and a dictionary
  // (actually just an object - it's a JS idiom) of parameters.
  function rpcCall(name, params) {
    if (this_.rpc_available) {
      // Construct the URL for the RPC request.
      var args = [];
      for (var pname in params) {
        pvalue = params[pname];
        args.push(encodeURIComponent(pname) + '=' + encodeURIComponent(pvalue));
      }
      var url = '/TESTER/' + name + '?' + args.join('&');
      var req = new XMLHttpRequest();
      // Async result handler
      if (this_.async) {
        req.onreadystatechange = function() {
          if (req.readyState == XMLHttpRequest.DONE) {
            handleRPCResponse(name, req);
          }
        }
      }
      try {
        req.open('GET', url, this_.async);
        req.send();
        if (!this_.async) {
          handleRPCResponse(name, req);
        }
      } catch (err) {
        handleRPCFailure(name, err.toString());
      }
    }
  }

  // Pretty prints an error into the DOM.
  this.logLocalError = function(message) {
    this.logLocal(message, 'red');
    this.visualError();
  }

  // If RPC isn't working, disable it to stop error message spam.
  this.disableRPC = function() {
    if (this.rpc_available) {
      this.rpc_available = false;
      this.logLocal('Disabling RPC', 'gray');
    }
  }

  this.startup = function() {
    // TODO(ncbray) move into test runner
    this.num_passed = 0;
    this.num_failed = 0;
    this.num_errors = 0;
    this._log('[STARTUP]');
  }

  this.shutdown = function() {
    if (this.num_passed == 0 && this.num_failed == 0 && this.num_errors == 0) {
      this.client_error('No tests were run. This may be a bug.');
    }
    var full_message = '[SHUTDOWN] ';
    full_message += this.num_passed + ' passed';
    full_message += ', ' + this.num_failed + ' failed';
    full_message += ', ' + this.num_errors + ' errors';
    this.logLocal(full_message);
    rpcCall('Shutdown', {message: full_message, passed: !this.ever_failed});

    if (this.ever_failed) {
      this.localOutput.style.border = '2px solid #FF0000';
    } else {
      this.localOutput.style.border = '2px solid #00FF00';
    }
  }

  this.ping = function() {
    rpcCall('Ping', {});
  }

  this.client_error = function(message) {
    this.num_errors += 1;
    this.visualError();
    var full_message = '\n[CLIENT_ERROR] ' + exceptionToLogText(message)
    // The client error could have been generated by logging - be careful.
    try {
      this._log(full_message, 'red');
    } catch (err) {
      // There's not much that can be done, at this point.
    }
  }

  this.begin = function(test_name) {
    var full_message = '[' + test_name + ' BEGIN]'
    this._log(full_message, 'blue');
  }

  // TODO(ncbray) make this the main interface
  this._log = function(message, color) {
    if (typeof(message) != 'string') {
      message = toString(message);
    }
    this.logLocal(message, color);
    rpcCall('TestLog', {message: message});
  }

  this.log = function(test_name, message) {
    if (message == undefined) {
      // This is a log message that is not assosiated with a test.
      // What we though was the test name is actually the message.
      this._log(test_name);
    } else {
      if (typeof(message) != 'string') {
        message = toString(message);
      }
      this._log('[' + test_name + ' LOG] ' + message);
    }
  }

  this.fail = function(test_name, message) {
    this.num_failed += 1;
    this.visualError();
    var full_message = '[' + test_name + ' FAIL] ' + message
    this._log(full_message, 'red');
  }

  this.exception = function(test_name, err) {
    this.num_errors += 1;
    this.visualError();
    var message = exceptionToLogText(err);
    var full_message = '[' + test_name + ' EXCEPTION] ' + message;
    this._log(full_message, 'purple');
  }

  this.pass = function(test_name) {
    this.num_passed += 1;
    var full_message = '[' + test_name + ' PASS]';
    this._log(full_message, 'green');
  }

  this.blankLine = function() {
    this._log('');
  }

  this.visualError = function() {
    // Changing the color is defered until testing is done
    this.ever_failed = true;
  }

  this.logLineLocal = function(text, color) {
    text = text.replace(/\s+$/, '');
    if (text == '') {
      this.localOutput.appendChild(document.createElement('br'));
    } else {
      var mNode = document.createTextNode(text);
      var div = document.createElement('div');
      // Preserve whitespace formatting.
      div.style['white-space'] = 'pre';
      if (color != undefined) {
        div.style.color = color;
      }
      div.appendChild(mNode);
      this.localOutput.appendChild(div);
    }
  }

  this.logLocal = function(message, color) {
    var lines = message.split('\n');
    for (var i = 0; i < lines.length; i++) {
      this.logLineLocal(lines[i], color);
    }
  }

  // Create a place in the page to output test results
  this.localOutput = document.createElement('div');
  this.localOutput.style.border = '2px solid #0000FF';
  this.localOutput.style.padding = '10px';
  document.body.appendChild(this.localOutput);
}


//
// BEGIN functions for testing
//


function fail(message, info) {
  var parts = [];
  if (message != undefined) {
    parts.push(message);
  }
  if (info != undefined) {
    parts.push('(' + info + ')');
  }
  throw {type: 'test_fail', message: parts.join(' ')};
}


function assert(condition, message) {
  if (!condition) {
    fail(message, toString(condition));
  }
}


// This is accepted best practice for checking if an object is an array.
function isArray(obj) {
  return Object.prototype.toString.call(obj) === '[object Array]';
}


function toString(obj) {
  if (typeof(obj) == 'string') {
    return '\'' + obj + '\'';
  }
  try {
    return obj.toString();
  } catch (err) {
    try {
      // Arrays should do this automatically, but there is a known bug where
      // NaCl gets array types wrong.  .toString will fail on these objects.
      return obj.join(',');
    } catch (err) {
      if (obj == undefined) {
        return 'undefined';
      } else {
        // There is no way to create a textual representation of this object.
        return '[UNPRINTABLE]';
      }
    }
  }
}


function assertEqual(a, b, message) {
  if (isArray(a) && isArray(b)) {
    assertArraysEqual(a, b, message);
  } else if (a !== b) {
    fail(message, toString(a) + ' != ' + toString(b));
  }
}


function assertArraysEqual(a, b, message) {
  var dofail = function() {
    fail(message, toString(a) + ' != ' + toString(b));
  }
  if (a.length != b.length) {
    dofail();
  }
  for (var i = 0; i < a.length; i++) {
    if(a[i] != b[i]) {
      dofail();
    }
  }
}


// Ideally there'd be some way to identify what exception was thrown, but JS
// exceptions are fairly ad-hoc.
// TODO(ncbray) allow manual validation of exception types?
function assertRaises(func, message) {
  try {
    func();
  } catch (err) {
    return;
  }
  fail(message, 'did not raise');
}


function halt_and_pass() {
  throw {type: 'test_pass'};
}


function halt_and_callback(time, callback) {
  throw {type: 'test_wait', time: time, callback: callback};
}


//
// END functions for testing
//


function begins_with(s, prefix) {
  if (s.length >= prefix.length) {
    return s.substr(0, prefix.length) == prefix;
  } else {
    return false;
  }
}


function ends_with(s, suffix) {
  if (s.length >= suffix.length) {
    return s.substr(s.length - suffix.length, suffix.length) == suffix;
  } else {
    return false;
  }
}


function embed_name(embed) {
  if (embed.name != undefined) {
    if (embed.id != undefined) {
      return embed.name + ' / ' + embed.id;
    } else {
      return embed.name;
    }
  } else if (embed.id != undefined) {
    return embed.id;
  } else {
    return '[no name]';
  }
}


function NaClWaiter(body_element) {
  // Work around how JS binds 'this'
  var this_ = this;
  var embedsToWaitFor = [];
  // embedsLoaded contains list of embeds that have dispatched the
  // 'loadend' progress event.
  this.embedsLoaded = [];

  this.is_loaded = function(embed) {
    for (var i = 0; i < this_.embedsLoaded.length; ++i) {
      if (this_.embedsLoaded[i] === embed) {
        return true;
      }
    }
    return embed.__moduleReady == 1;
  }

  this.has_errored = function(embed) {
    var msg = embed.lastError;
    return embed.lastError != undefined && embed.lastError != '';
  }

  // If an argument was passed, it is the body element for registering
  // event listeners for the 'loadend' event type.
  if (body_element != undefined) {
    var eventListener = function(e) {
      if (e.type == 'loadend') {
        this_.embedsLoaded.push(e.target);
      }
    }

    body_element.addEventListener('loadend', eventListener, true);
  }

  // Takes an arbitrary number of arguments.
  this.waitFor = function() {
    for (var i = 0; i< arguments.length; i++) {
      embedsToWaitFor.push(arguments[i]);
    }
  }

  this.run = function(doneCallback, pingCallback) {
    this.doneCallback = doneCallback;
    this.pingCallback = pingCallback;

    // Wait for up to thirty seconds for the nexes to load.
    // TODO(ncbray) use error handling mechanisms (when they are implemented)
    // rather than a timeout.
    this.totalWait = 0;
    this.maxTotalWait = 90000;
    this.retryWait = 10;
    this.waitForPlugins();
  }

  this.waitForPlugins = function() {
    var errored = [];
    var loaded = [];
    var waiting = [];

    for (var i = 0; i < embedsToWaitFor.length; i++) {
      try {
        var e = embedsToWaitFor[i];
        if (this.has_errored(e)) {
          errored.push(e);
        } else if (this.is_loaded(e)) {
          loaded.push(e);
        } else {
          waiting.push(e);
        }
      } catch(err) {
        // If the module is badly horked, touching lastError, etc, may except.
        errored.push(err);
      }
    }

    this.totalWait += this.retryWait;

    if (waiting.length == 0) {
      this.doneCallback(loaded, errored);
    } else if (this.totalWait >= this.maxTotalWait) {
      // Timeouts are considered errors.
      this.doneCallback(loaded, errored.concat(waiting));
    } else {
      setTimeout(function() { this_.waitForPlugins(); }, this.retryWait);
      // Capped exponential backoff
      this.retryWait += this.retryWait/2;
      // Paranoid: does setTimeout like floating point numbers?
      this.retryWait = Math.round(this.retryWait);
      if (this.retryWait > 100)
        this.retryWait = 100;
      // Prevent the server from thinking the test has died.
      if (this.pingCallback)
        this.pingCallback();
    }
  }

}


function Tester(body_element) {
  // Workaround how JS binds 'this'
  var this_ = this;
  // The tests being run.
  var tests = [];
  this.rpc = new RPCWrapper();
  this.waiter = new NaClWaiter(body_element);

  var load_errors_are_test_errors = true;

  //
  // BEGIN public interface
  //

  this.loadErrorsAreOK = function() {
    load_errors_are_test_errors = false;
  }

  this.log = function(message) {
    this.rpc.log(this.currentTest, message);
  }

  this.addTest = function(name, testFunction) {
    tests.push({name: name, callback: testFunction});
  }

  // TODO(ncbray): implement parallelized async test harness
  this.waitForCallback = function(callbackName, expectedCalls) {
    this_.log('Waiting for ' + expectedCalls + ' invocations of callback: '
               + callbackName);
    var gotCallbacks = 0;

    // Deliberately global - this what the nexe expects.
    // TODO(ncbray): consider returning this function, so the test has more
    // flexibility. For example, in the test one could count to N
    // using a different callback before calling _this_ callback, and
    // continuing the test. Also, consider calling user-supplieed callback
    // when done waiting.
    window[callbackName] = function() {
      ++gotCallbacks;
      this_.log('Received callback ' + gotCallbacks);
    };

    function wait() {
      if (gotCallbacks < expectedCalls) {
        halt_and_callback(1, wait);
      } else {
        this_.log("Done waiting");
      }
    }

    wait();
  }

  this.run = function() {
    this.rpc.startup();

    this.waiter.run(
      function(loaded, waiting) {
        for (var i = 0; i < loaded.length; i++) {
          this_.rpc.log(embed_name(loaded[i]) + ' loaded');
        }
        // Be careful when interacting with horked nexes.
        var getCarefully = function (callback) {
          try {
            return callback();
          } catch (err) {
            return '<exception>';
          }
        }
        for (var j = 0; j < waiting.length; j++) {
          var name = getCarefully(function(){
            return embed_name(waiting[j]);
          });
          var ready = getCarefully(function(){
            return toString(waiting[j].__moduleReady);
          });
          var last = getCarefully(function(){
            return toString(waiting[j].lastError);
          });
          var msg = (name + ' did not load. Status: ' + ready + ' / ' + last);
          if(load_errors_are_test_errors) {
            this_.rpc.client_error(msg);
          } else {
            this_.rpc.log(msg);
          }
        }
        this_.startTesting();
      },
      function() {
        this_.rpc.ping();
      }
    );
  }

  // Takes an arbitrary number of arguments.
  this.waitFor = function() {
    for (var i = 0; i< arguments.length; i++) {
      this.waiter.waitFor(arguments[i]);
    }
  }

  //
  // END public interface
  //

  this.initTest = function() {
    if (this.testIndex < tests.length) {
      // Setup for the next test.
      var test = tests[this.testIndex];
      this.currentTest = test.name;
      this.rpc.blankLine();
      this.rpc.begin(this.currentTest);
      this.setNextStep(0, test.callback);
    } else {
      // There are no more test suites.
      this.rpc.blankLine();
      this.rpc.shutdown();
    }
  }

  this.setNextStep = function(time, callback) {
    // Give up control
    // There are three reasons for this:
    // 1) It allows the render thread to update (can't see the log, otherwise)
    // 2) It breaks up a "long running process" so the browser
    //    won't think it crashed
    // 3) It allows us to sleep for a specified interval
    // TODO it might not be desirable to relinquish control between each test.
    // Running several tests in a row might make things faster.
    this.nextStep = callback;
    setTimeout(function() { this_.runTestStep(); }, time);
  }

  this.startTesting = function() {
    // if tests[0] does not exist (no tests), initTest will shut down testing.
    this.testIndex = 0;
    this.initTest();
  }

  this.nextTest = function() {
    // Advance to the next test suite
    this.testIndex += 1;
    this.initTest()
  }

  this.runTestStep = function() {
    callback = this.nextStep;
    // Be paranoid - avoid accidental infinite loops
    this.nextStep = null;
    // Should we move on to the next test?
    var done = true;
    // Did the text exit abnormally
    var exceptionHandled = false;

    try {
      callback();
    } catch (err) {
      if (typeof err == 'object') {
        if ('type' in err) {
          if (err.type == 'test_fail') {
            // A special exception that terminates the test with a failure
            this.rpc.fail(this.currentTest, err.message);
            exceptionHandled = true;
          } else if (err.type == 'test_pass') {
            // A special exception that terminates the test without failing
            this.rpc.pass(this.currentTest);
            exceptionHandled = true;
          } else if (err.type == 'test_wait') {
            // A special exception that indicates the test wants a callback
            this.setNextStep(err.time, err.callback);
            done = false;
            exceptionHandled = true;
          }
        }
      }
      if (!exceptionHandled) {
        // This is not a special type of exception, it is an error.
        this.rpc.exception(this.currentTest, err);
        exceptionHandled = true
      }
    }

    if (done) {
      if (!exceptionHandled) {
        // No exception, the test passed
        this.rpc.pass(this.currentTest);
      }
      this.nextTest();
    }
  }
}
