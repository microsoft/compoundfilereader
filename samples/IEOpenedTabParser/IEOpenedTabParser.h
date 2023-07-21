/**
    IE opened tab dat file parser
    opened tab files are in %localappdata%\Microsoft\Internet Explorer\TabRoaming\{GUID}\NNNN, (N is digit 0-9). 
    They are compound file.
*/

#include <compoundfilereader.h>
#include <utf.h>
#include <string>
#include <limits>
#include <vector>

struct OPENED_TAB_INFO
{
    std::wstring url;
    std::wstring title;
    std::wstring faviconUrl;
};

struct OpenedTabFileParser
{
    static const CFB::COMPOUND_FILE_ENTRY* GetOpenedTabPropertyStream(CFB::CompoundFileReader& reader)
    {
        const CFB::COMPOUND_FILE_ENTRY* entry = nullptr;
        reader.EnumFiles(reader.GetRootEntry(), -1, 
            [&](const CFB::COMPOUND_FILE_ENTRY* e, const CFB::utf16string&, int)->void
        {
            if (reader.IsPropertyStream(e))
            {
                entry = e;
            }
        });

        return entry;
    }

    static bool GetOpenedTabInfo(const void* buffer, size_t bufferLen, OPENED_TAB_INFO* info)
    {
        CFB::CompoundFileReader reader(buffer, bufferLen);
        const CFB::COMPOUND_FILE_ENTRY* propertyFile = GetOpenedTabPropertyStream(reader);

        bool ret = false;
        if (propertyFile != nullptr && propertyFile->size <= std::numeric_limits<size_t>::max())
        {
            size_t size = static_cast<size_t>(propertyFile->size);

            char* data = new char[size];
            reader.ReadFile(propertyFile, 0, data, size);
            CFB::PropertySetStream propertySetStream(data, size);
            CFB::PropertySet propertySet = propertySetStream.GetPropertySet(0);
            info->url = UTF16ToWstring(propertySet.GetStringProperty(3));
            info->title = UTF16ToWstring(propertySet.GetStringProperty(5));
            info->faviconUrl = UTF16ToWstring(propertySet.GetStringProperty(1002));
            ret = true;
            delete [] data;
        }

        return ret;
    }
};
