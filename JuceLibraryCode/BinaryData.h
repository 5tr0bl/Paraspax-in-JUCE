/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   about_psx_txt;
    const int            about_psx_txtSize = 745;

    extern const char*   psx_json;
    const int            psx_jsonSize = 3738524;

    extern const char*   LICENSE;
    const int            LICENSESize = 1452;

    extern const char*   CMakeLists_txt;
    const int            CMakeLists_txtSize = 482;

    extern const char*   CMakeLists_txt2;
    const int            CMakeLists_txt2Size = 2991;

    extern const char*   LICENSE_txt;
    const int            LICENSE_txtSize = 1104;

    extern const char*   LICENSE2;
    const int            LICENSE2Size = 1109;

    extern const char*   COPYING_txt;
    const int            COPYING_txtSize = 246;

    extern const char*   LICENSE3;
    const int            LICENSE3Size = 1070;

    extern const char*   COPYING;
    const int            COPYINGSize = 1774;

    extern const char*   README;
    const int            READMESize = 5302;

    extern const char*   CMakeLists_txt3;
    const int            CMakeLists_txt3Size = 1954;

    extern const char*   CMakeLists_txt4;
    const int            CMakeLists_txt4Size = 16367;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 13;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
