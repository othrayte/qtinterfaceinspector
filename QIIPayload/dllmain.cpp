#include "qiipayload.h"

#include <windows.h>

#include <QGuiApplication>
#include <QDebug>
#include <QFileInfo>

//-------------------------------------------------------
// DllMain
// Notice: retrieves the password, when mapped into the
//		   remote process (g_hPwdEdit != 0);
//
bool APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		qDebug() << "[QIIPayload]"
				 << "attaching";
		if (auto app = QGuiApplication::instance()) {
			TCHAR moduleFile[MAX_PATH] = L"";
			GetModuleFileName((HMODULE)hModule, moduleFile, _countof(moduleFile));
			QString payloadLocation = QFileInfo(QString::fromStdWString(std::wstring(moduleFile))).canonicalPath();

			qDebug() << "[QIIPayload]"
					 << "found GUI application";
			auto payload = new QiiPayload(payloadLocation);
			payload->moveToThread(app->thread());

			qDebug() << "[QIIPayload]"
					 << "starting payload";
			QMetaObject::invokeMethod(payload, "start", Qt::QueuedConnection);

			qDebug() << "[QIIPayload]"
					 << "payload started, leaving";
			::LoadLibrary(moduleFile);
		} else {
			qDebug() << "[QIIPayload]"
					 << "couldn't find the GUI application, maybe using non-matching Qt (debug/release)";
			::MessageBeep(MB_ICONERROR);
		}
	}

	return true;
}
