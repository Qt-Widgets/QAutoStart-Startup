#include "qautostart_p.h"
#include <QSettings>

bool QAutoStartPrivate::isAutoStartEnabled()
{
	createSettings();
	return _settings->contains(startId);
}

bool QAutoStartPrivate::setAutoStartEnabled(bool autoStartEnabled)
{
	createSettings();
	if(_settings->isWritable()) {
		const auto current = _settings->contains(startId);
		if(current != autoStartEnabled) {
			if(autoStartEnabled)
				_settings->setValue(startId, createCommand());
			else
				_settings->remove(startId);
			_settings->sync();
			return true;
		} else
			return true;
	} else
		return false;
}

void QAutoStartPrivate::createSettings()
{
	if(!_settings) {
		if(extraProperties.contains(QAutoStart::CustomLocation))
			_settings = new QSettings{extraProperties.value(QAutoStart::CustomLocation).toString(), QSettings::NativeFormat, q_ptr};
		else
			_settings = new QSettings{QStringLiteral("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), QSettings::NativeFormat, q_ptr};
	} else
		_settings->sync();
}
