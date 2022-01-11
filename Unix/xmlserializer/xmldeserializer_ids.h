/*++ 
    Copyright (C) Microsoft Corporation
--*/

#if defined(RC_INVOKED)
#define ID_MI_DES_XML_ELEM_DUP_UNK_ATTR 4000
#define ID_MI_DES_XML_ELEM_MISSING_ATTR 4001
#define ID_MI_DES_XML_INST_TOO_MANY_CLASSES 4002
#define ID_MI_DES_XML_INST_CANNOT_FIND_CLASS 4003
#define ID_MI_DES_XML_CLASS_DERIVATION_LIST_WRONG 4004
#define ID_MI_DES_XML_CLASS_SUPERCLASS_PARENT_MISMATCH 4005
#define ID_MI_DES_XML_ELEM_CHILD_UNK 4006
#define ID_MI_DES_XML_EMPTY_VAL_NOT_STRING 4007
#define ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED 4008
#define ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED 4009
#define ID_MI_DES_XML_ELEM_HAS_NO_CHILDREN 4010
#define ID_MI_DES_XML_ELEM_INVALID_EMBED_CLASS_NAME 4011
#define ID_MI_DES_XML_ELEM_MISSING_ELEM 4012
#define ID_MI_DES_XML_REF_TO_VALUE_NOT_SUPPORTED 4013
#define ID_MI_DES_XML_KEYVALUE_FOR_NON_KEY 4014
#define ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH 4015
#define ID_MI_DES_XML_INSTANCENAME_COULD_NOT_FIND_KEY 4016
#define ID_MI_DES_XML_ELEM_VAL_NO_DATA 4017
#else
#define ID_MI_DES_XML_ELEM_DUP_UNK_ATTR                 PAL_T("Failed to deserialize CIM-XML document. %T XML element has duplicate or unknown attribute %T.")
#define ID_MI_DES_XML_ELEM_MISSING_ATTR                 PAL_T("Failed to deserialize CIM-XML document. %T XML element has missing attribute %T.")
#define ID_MI_DES_XML_INST_TOO_MANY_CLASSES             PAL_T("Failed to deserialize CIM-XML document. The instance is too complex to deserialize because it uses too many classes.")
#define ID_MI_DES_XML_INST_CANNOT_FIND_CLASS            PAL_T("Failed to deserialize CIM-XML document. Could not find the class definition %T while deserializing instance.")
#define ID_MI_DES_XML_CLASS_DERIVATION_LIST_WRONG       PAL_T("Failed to deserialize CIM-XML document. A class definition has a SUPERCLASS attribute and a DERIVATION attribute. The SUPERCLASS attribute value should be the first item in the DERIVATION attribute list." )
#define ID_MI_DES_XML_CLASS_SUPERCLASS_PARENT_MISMATCH PAL_T("Failed to deserialize CIM-XML document. While decoding a class definition there was a mismatch between the SUPERCLASS attribute and the passed in parent class definition." )
#define ID_MI_DES_XML_ELEM_CHILD_UNK                    PAL_T("Failed to deserialize CIM-XML document. %T XML element has duplicate or unknown child element %T.")
#define ID_MI_DES_XML_EMPTY_VAL_NOT_STRING              PAL_T("Failed to deserialize CIM-XML document. Empty VALUE XML elements must be of string type.")
#define ID_MI_DES_XML_ATTR_VAL_CONVERSION_FAILED        PAL_T("Failed to deserialize CIM-XML document. %T XML element has an attribute %T with an invalid value.")
#define ID_MI_DES_XML_ELEM_VAL_CONVERSION_FAILED        PAL_T("Failed to deserialize CIM-XML document. %T XML element has a VALUE with an invalid value.")
#define ID_MI_DES_XML_ELEM_HAS_NO_CHILDREN              PAL_T("Failed to deserialize CIM-XML document. %T XML element has no children when one or more were expected.")
#define ID_MI_DES_XML_ELEM_INVALID_EMBED_CLASS_NAME     PAL_T("Failed to deserialize CIM-XML document. %T XML element has attribute EmbeddedClassName when the %T is not an embedded instance.")
#define ID_MI_DES_XML_ELEM_MISSING_ELEM                 PAL_T("Failed to deserialize CIM-XML document. %T XML element has missing child element %T.")
#define ID_MI_DES_XML_REF_TO_VALUE_NOT_SUPPORTED        PAL_T("Failed to deserialize CIM-XML document. VALUE.REFERENCE of types CLASSPATH, LOCALCLASSPATH or CLASSNAME are not supported.")
#define ID_MI_DES_XML_KEYVALUE_FOR_NON_KEY              PAL_T("Failed to deserialize CIM-XML document. A KEYVALUE was found for a non-key property.")
#define ID_MI_DES_XML_KEYVALUE_TYPE_MISMATCH           PAL_T("Failed to deserialize CIM-XML document. A KEYVALUE type does not match the class declaration.")
#define ID_MI_DES_XML_INSTANCENAME_COULD_NOT_FIND_KEY   PAL_T("Failed to deserialize CIM-XML document. INSTANCENAME XML element has implied a key name, but no keys were found in the class declaration.")
#define ID_MI_DES_XML_ELEM_VAL_NO_DATA                  PAL_T("Failed to deserialize CIM-XML document. %T XML element has no value.")
#endif
