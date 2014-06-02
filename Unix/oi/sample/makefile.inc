$(OBJ_PATH)\$O\Frog_Gen.c : Frog.h
    oigen.exe $? FrogProvider {F93D404F-F291-496E-9D8D-56D8C6F8F650} $@

