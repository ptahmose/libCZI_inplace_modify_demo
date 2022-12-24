#pragma once

#include <string>
#include <InplaceModifyDemo_Config.h>

class CCmdLineOptions
{
private:
    std::wstring czi_filename_;
public:
    /// Parse the command line arguments. The arguments are expected to have
    /// UTF8-encoding.
    ///
    /// \param          argc    The number of arguments.
    /// \param [in]     argv    Pointer to an array with the null-terminated, UTF8-encoded arguments.
    ///
    /// \returns    True if it succeeds, false if it fails.
    [[nodiscard]] bool Parse(int argc, char** argv);

    [[nodiscard]] const std::wstring& GetCZIFilenameW() const;
};