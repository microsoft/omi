#!/bin/sh

# translate strings.def into (project-wide) messages.pot
# -E = only preprocessor is run, no complier or linker

cpp strings.def -E -I ../.. -include output/include/config.h -include pal/intlstr.xgettext.inc | xgettext --language=C - --indent --foreign-user --output=messages.pot

# artificially translate messages.po into pt_BR.po
rm -rf pt_BR*
msginit --input=messages.pot --locale=pt_BR --no-translator
sed --in-place pt_BR.po --expression='N;/msgid.*\nmsgstr.*/s/msgid "\([^"]\+\)".*/msgid "\1"\nmsgstr "This is a localized string. \1"/;P;D'

# translate pt_BR.po into pt_BR.mo
msgfmt --check-format pt_BR.po --output-file=pt_BR.mo --verbose

# copy the binary and .mo files into the right relative locations
cp ../../output/bin/pal_intlstr_sample .
mkdir -p ./pt_BR/LC_MESSAGES
cp pt_BR.mo ./pt_BR/LC_MESSAGES/pal_intlstr_sample.exe.mo

# run the test
export LANGUAGE=
export LANG=
./pal_intlstr_sample
export LANG=pt_BR
./pal_intlstr_sample


