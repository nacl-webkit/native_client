/* /gen/nacl_disallows_impl.h
 * THIS FILE IS AUTO_GENERATED DO NOT EDIT.
 *
 * This file was auto-generated by enum_gen.py
 * from file nacl_disallows.enum
 */

/* Define the corresponding names of NaClDisallowsFlag. */
static const char* const g_NaClDisallowsFlagName[NaClDisallowsFlagEnumSize + 1] = {
  "NaClTooManyPrefixBytes",
  "NaClMarkedIllegal",
  "NaClMarkedInvalid",
  "NaClMarkedSystem",
  "NaClHasBadSegmentPrefix",
  "NaClCantUsePrefix67",
  "NaClMultipleRexPrefix",
  "NaClRepDisallowed",
  "NaClRepneDisallowed",
  "NaClData16Disallowed",
  "NaClHasDuplicatePrefix",
  "NaClHasAmbigSegmentPrefixes",
  "NaClRexPrefixNotLast",
  "NaClDisallowsFlagEnumSize"
};

const char* NaClDisallowsFlagName(NaClDisallowsFlag name) {
  return name <= NaClDisallowsFlagEnumSize
    ? g_NaClDisallowsFlagName[name]
    : "NaClDisallowsFlag???";
}
