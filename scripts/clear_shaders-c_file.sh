#! /bin/bash

shader_c="$1"

if [[ -f $shader_c ]]; then
    rm $shader_c
fi
echo "#include <shaders.h>" > $shader_c
echo "// File generated with very clever make script. please don't touch with your hands. ;<" >> $shader_c
echo "" >> $shader_c
