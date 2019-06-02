// Copyright (c) 2010-2017 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAINOTIFICATIONSIOS_H
#define	MOAINOTIFICATIONSIOS_H

#if 0

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <moai-core/headers.h>

//================================================================//
// MOAINotificationsIOS
//================================================================//
/**	@lua	MOAINotificationsIOS
	@text	Wrapper for push notification integration on iOS 
			devices. Exposed to Lua via MOAINotifications on all
			mobile platforms.

	@const	REMOTE_NOTIFICATION_REGISTRATION_COMPLETE	Event code for notification registration completion.
	@const	REMOTE_NOTIFICATION_MESSAGE_RECEIVED		Event code for a push notification message receipt.

	@const	REMOTE_NOTIFICATION_RESULT_REGISTERED		Error code for a successful notification registration.
	@const	REMOTE_NOTIFICATION_RESULT_UNREGISTERED		Error code for a successful notification deregistration.
	@const	REMOTE_NOTIFICATION_RESULT_ERROR			Error code for a failed notification registration or deregistration.
	
	@const	REMOTE_NOTIFICATION_NONE					Notification type none.
	@const	REMOTE_NOTIFICATION_BADGE					Notification type icon badges.
	@const	REMOTE_NOTIFICATION_SOUND					Notification type sound.
	@const	REMOTE_NOTIFICATION_ALERT					Notification type alerts.
*/
class MOAINotificationsIOS :
	public ZLContextClass < MOAINotificationsIOS >,
	public virtual MOAILuaObject {
private:

	//----------------------------------------------------------------//
	static int	_getAppIconBadgeNumber				( lua_State* L );
	static int	_localNotificationInSeconds			( lua_State* L );
	static int	_registerForRemoteNotifications		( lua_State* L );
	static int	_setAppIconBadgeNumber				( lua_State* L );
	static int	_setListener						( lua_State* L );
	static int	_unregisterForRemoteNotifications	( lua_State* L );

public:

	DECL_LUA_SINGLETON ( MOAINotificationsIOS )

	enum {
		LOCAL_NOTIFICATION_MESSAGE_RECEIVED,
		REMOTE_NOTIFICATION_REGISTRATION_COMPLETE,
		REMOTE_NOTIFICATION_MESSAGE_RECEIVED,
		TOTAL
	};

	enum {
   		REMOTE_NOTIFICATION_RESULT_REGISTERED,
		REMOTE_NOTIFICATION_RESULT_UNREGISTERED,
    	REMOTE_NOTIFICATION_RESULT_ERROR,
	};
	
	MOAILuaStrongRef		mListeners [ TOTAL ];

			MOAINotificationsIOS				();
			~MOAINotificationsIOS				();
	void	NotifyRemoteDeregistrationComplete	();
	void	NotifyLocalNotificationReceived     ( UILocalNotification* notification );
	void	NotifyRemoteNotificationReceived	( NSDictionary* notification );
	void	NotifyRemoteRegistrationComplete	( NSData* token, NSError *error );
	void	MOAILuaObject_RegisterLuaClass					( MOAIComposer& composer, MOAILuaState& state );
};

#endif  //DISABLE_NOTIFICATIONS

#endif  //MOAINOTIFICATIONS_H
