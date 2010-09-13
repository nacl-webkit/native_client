// Copyright (c) 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "native_client/src/shared/ppapi_proxy/browser_globals.h"
#include <map>

namespace ppapi_proxy {

// All of these methods are called from the browser main (UI, JavaScript, ...)
// thread.

namespace {

std::map<PP_Instance, BrowserPpp*>* instance_to_ppp_map = NULL;
// The GetInterface pointer from the browser.
PPB_GetInterface get_interface;
// For efficiency, cached results from GetInterface.
const PPB_Core* core_interface;
const PPB_Var* var_interface;

}  // namespace

void SetBrowserPppForInstance(PP_Instance instance, BrowserPpp* browser_ppp) {
  // If there was no map, create one.
  if (instance_to_ppp_map == NULL) {
    instance_to_ppp_map = new std::map<PP_Instance, BrowserPpp*>;
  }
  // Add the instance to the map.
  (*instance_to_ppp_map)[instance] = browser_ppp;
}

void UnsetBrowserPppForInstance(PP_Instance instance) {
  if (instance_to_ppp_map == NULL) {
    // Something major is wrong here.  We are deleting a map entry
    // when there is no map.
    // TODO(sehr): a CHECK here would be appropriate if we had one in NaCl.
    return;
  }
  // Erase the instance from the map.
  instance_to_ppp_map->erase(instance);
  // If there are no more instances alive, remove the map.
  if (instance_to_ppp_map->size() == 0) {
    delete instance_to_ppp_map;
    instance_to_ppp_map = NULL;
  }
}

BrowserPpp* LookupBrowserPppForInstance(PP_Instance instance) {
  if (instance_to_ppp_map == NULL) {
    return NULL;
  }
  return (*instance_to_ppp_map)[instance];
}

void SetBrowserGetInterface(PPB_GetInterface get_interface_function) {
  get_interface = get_interface_function;
  const void* core = (*get_interface_function)(PPB_CORE_INTERFACE);
  core_interface = reinterpret_cast<const PPB_Core*>(core);
  const void* var = (*get_interface_function)(PPB_VAR_INTERFACE);
  var_interface = reinterpret_cast<const PPB_Var*>(var);
}

const void* GetBrowserInterface(const char* interface_name) {
  return (*get_interface)(interface_name);
}

const PPB_Core* CoreInterface() {
  return core_interface;
}

const PPB_Var* VarInterface() {
  return var_interface;
}

}  // namespace ppapi_proxy
