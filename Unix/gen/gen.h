/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

#ifndef _gen_gen_h
#define _gen_gen_h

#include <string>
#include <vector>

struct GeneratorOptions
{
    // List of directories to search for included MOF files.
    std::vector<std::string> paths;

    // Generate Description qualifiers (in schema.c) if true.
    // Set MI_MODULE_FLAG_DESCRIPTIONS bit of MI_Module.flags.
    bool descriptions;

    // Generate Values/ValueMap qualifiers (in schema.c) if true.
    // Set MI_MODULE_FLAG_VALUES bit of MI_Module.flags.
    bool values;

    // Generate MappingStrings (in schema.c) if true.
    // Set MI_MODULE_FLAG_MAPPING_STRINGS bit of MI_Module.flags.
    bool mappingStrings;

    // Generate standard qualifier declarations (schema.c).
    // Set MI_MODULE_FLAG_STANDARD_QUALIFIERS bit of MI_Module.flags.
    bool standardQualifiers;

    // Generate boolean qualifiers (in addition to setting the corresponding
    // bit in the flags mask. Set MI_MODULE_FLAG_BOOLEANS bit  of
    // MI_Module.flags.
    bool booleanQualifiers;

    // Do not generate any qualifier declarations.
    bool ignoreAllQualifiers;

    // Set MI_MODULE_FLAG_FILTER_SUPPORT bit of MI_Module.flags.
    bool filterSupport;

    // Operate quietly if true (do not print anything to standard output.
    bool quiet;

    // Do not generate any providers if true (only class files and RTTI).
    bool noProviders;

    // Include all classes encountered during parsing in generated output.
    bool all;

    // Generate C++ output (class files and provider files). Set the
    // MI_MODULE_FLAG_CPLUSPLUS bit of MI_Module.flags.
    bool cpp;

    // Change the name of the generated schema declaration (in schema.c) to
    // this name (the default is schemaDecl).
    std::string schema;

    // Place all output files in this directory. If empty, place output files
    // in the current directory.
    std::string dir;

    // If true generate strings.rc file with English localized strings from
    // MOF files (applies to string and string[] qualifiers).
    bool localize;

    // Create a provider registry file with this name (if non-empty).
    std::string providerRegistryPath;

    // Generate *_AssociatorInstances and *_ReferenceInstances provider 
    // functions if true. Else generate role-oriented functions named as
    // follows:
    //
    //     <ASSOCIATION>_AssociatorInstances<ROLE1>
    //     <ASSOCIATION>_AssociatorInstances<ROLE2>
    //     <ASSOCIATION>_ReferenceInstances<ROLE1>
    //     <ASSOCIATION>_ReferenceInstances<ROLE2>
    //
    // Where ROLE1 and ROLE2 are the role names (reference names) in an
    // association. For example:
    //
    //     [Association]
    //     class Link
    //     {
    //         [Key] Gadget REF Left; /* <ROLE1> */
    //         [Key] Gadget REF Right; /* <ROLE2> */
    //     };
    //
    // In this example, the generator produces four provider functions with
    // the following names.
    //
    //     Link_AssociatorInstancesLeft
    //     Link_AssociatorInstancesRight
    //     Link_ReferenceInstancesLeft
    //     Link_ReferenceInstancesRight
    //
    bool association;

    // Generate class files (but not providers) for these extra classes.
    std::vector<std::string> extraClasses;

    // Name of the module entry point if non-empty (default entry point name is
    // called MI_Main). This name must not include the parentheses.
    std::string entryPoint;

    // Print no warnings if true (otherwise print them).
    bool no_warnings;

    // Name of provider for which a GNUmakefile will be generated. Used as
    // basename of library name (e.g., lib<PROVIDERNAME>.so).
    std::string providerName;

    // Do not generate the GetInstance provider stub for these classes
    // Set MI_ProviderFT.GetInstances to NULL.
    std::vector<std::string> noGetInstance;

    // Entire command line (all arguments);
    // Required to generate make file
    std::string cmdLine;

    // Generate ModelCorrespondence qualifier if true.
    bool modelCorrespondence;

    // Default constructor (sets options to default values).
    GeneratorOptions();

};

int GeneratorMain(
    const std::string& programName,
    const std::vector<std::string>& mofFiles,
    const std::vector<std::string>& classNames,
    const GeneratorOptions& options);

#endif /* _gen_gen_h */
