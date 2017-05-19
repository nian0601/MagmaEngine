rd /s /q Engine

xcopy /e Solution\Engine\*.h Engine\Include\
del Engine\Include\stdafx.h

xcopy Libs\Engine_Debug.lib Engine\Lib\
xcopy Libs\Engine_Release.lib Engine\Lib\