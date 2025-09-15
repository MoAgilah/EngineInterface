Game Project Settings
This is the project that should:

Link to SFML .lib files

Run .exe with .dll dependencies

Consume the SFMLGameEngine.lib from your static lib project

VC++ Directories:

Include Directories:
$(SolutionDir)SFMLGameEngine\SFMLGameEngine\include

Library Directories:
$(SolutionDir)SFMLGameEngine\SFMLGameEngine\lib

Executable Directories:
$(SolutionDir)SFMLGameEngine\SFMLGameEngine\bin\$(Configuration);%(ExecutableDirectories)

Linker → Input → Additional Dependencies:

Debug:
sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib;sfml-network-d.lib;%(AdditionalDependencies)

Release:
sfml-graphics.lib;sfml-window.lib;sfml-system.lib;sfml-audio.lib;sfml-network.lib;%(AdditionalDependencies)

Tips
Rebuild the SFMLGameEngine project first (so Game can link its .lib)

Ensure that the DLLs are in the output folder (or use a post-build copy as mentioned before)

Check that your Game.exe runs from Game\x64\Debug, and not from an outdated path