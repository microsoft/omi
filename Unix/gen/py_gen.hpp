#ifndef INCLUDED_PY_GEN_HPP
#define INCLUDED_PY_GEN_HPP


#include "gen.h"
#include "Parser.h"


#include <string>
#include <vector>


int
GenSchemaSourceFile_Py (
    GeneratorOptions const& options,
    Parser& parser,
    std::vector<std::string> const& classNames);


int
GenMI_Main_Py (
    GeneratorOptions const& options,
    Parser& parser,
    std::vector<std::string> const& classNames);


#endif // INCLUDED_PY_GEN_HPP
