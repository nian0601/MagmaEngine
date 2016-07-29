rd /s /q Release

xcopy /e Solution\Engine\*.h Release\Include\
del Release\Include\stdafx.h

xcopy Libs\Engine_Debug.lib Release\Libs\
xcopy Libs\Engine_Release.lib Release\Libs\