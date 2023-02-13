# compoundfilereader
Simple standalone C++ header file to read compound file (Structured Storage File) content.

# Source code structure
- **src/include/compoundfilereader.h**
  The only header file needed for parsing compound file.
- **src/include/utf.h**
  The helper header file used for converting between utf16, utf8, and unicode. It's used by samples.
- **test/data**
  Real world compound files for tests.
- **samples/cfb**
  Command line tool to list and dump compound files.
- **samples/IEOpenedTabParser**
  Command line tool to show IE opened tab information.
- **vsproject**
  Project and solution files for Microsoft Visual Studio.

# Usage
- Copy compoundfilereader.h to your source tree
  or: install "compoundfilereader" by git submodule
- `#include <compoundfilereader.h>` in your source code
- Construct a **CompoundFileReader** object by giving the buffer (see compoundfilereader.h for details)

# Build the samples
## Linux
Run `make`
(requires gcc and g++)
## Windows
- Option 1: double click 'vsproject\cfbreader\cfbreader.sln' then build in Visual Studio
- Option 2: run 'build.bat' in Visual Studio Command Prompt
(requires Visual Studio)
## Run the samples
Try the following:
``` batchfile
out/ieot "test/data/{BC59C035-E8AC-11E4-825B-10604B7CB9F0}.dat"
out/cfb list "test/data/a test email message.msg"
out/cfb dump "test/data/a test email message.msg" __properties_version1.0
```

# TODO
- Unit tests
- Make the reader able to connect to abstract interfaces such as istream

# Microsoft Open Source Code of Conduct
This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
