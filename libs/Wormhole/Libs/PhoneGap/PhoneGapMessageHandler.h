/*
Copyright (C) 2011 MoSync AB

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA 02110-1301, USA.
*/

/*! \addtogroup WormHoleGroup
 *  @{
 */

/** @defgroup WormHoleGroup Wormhole Library
 *  @{
 */

/**
 * @file PhoneGapMessageHandler.h
 * @author Ali Sarrafi
 *
 * Handles JSON messages sent from JavaScript.
 */

#ifndef WORMHOLE_LIBS_PHONEGAP_PHONEGAPMESSAGEHANDLER_H_
#define WORMHOLE_LIBS_PHONEGAP_PHONEGAPMESSAGEHANDLER_H_

#include <NativeUI/WebView.h>
#include <MAUtil/String.h>
#include "../JSONMessage.h"
#include "PhoneGapSensors.h"
#include "PhoneGapFile.h"
#include "PhoneGapCapture.h"
#include "PhoneGapCamera.h"
#include "../W3C/SensorManager.h"
#include "../Notification/PushNotificationManager.h"

// PhoneGap callback result codes.
#define PHONEGAP_CALLBACK_STATUS_NO_RESULT "0"
#define PHONEGAP_CALLBACK_STATUS_OK "1"
#define PHONEGAP_CALLBACK_STATUS_CLASS_NOT_FOUND_EXCEPTION "2"
#define PHONEGAP_CALLBACK_STATUS_ILLEGAL_ACCESS_EXCEPTION "3"
#define PHONEGAP_CALLBACK_STATUS_INSTANTIATION_EXCEPTION "4"
#define PHONEGAP_CALLBACK_STATUS_MALFORMED_URL_EXCEPTION "5"
#define PHONEGAP_CALLBACK_STATUS_IO_EXCEPTION "6"
#define PHONEGAP_CALLBACK_STATUS_INVALID_ACTION "7"
#define PHONEGAP_CALLBACK_STATUS_JSON_EXCEPTION "8"
#define PHONEGAP_CALLBACK_STATUS_ERROR "9"

namespace Wormhole
{
	/**
	 * Class that implements JavaScript calls.
	 *
	 * The JavaScript side is in file extendedbridge.js.
	 */
	class PhoneGapMessageHandler:
		public MAUtil::SensorListener,
		public MAUtil::CustomEventListener
	{
	public:
		/**
		 * Constructor.
		 */
		PhoneGapMessageHandler(NativeUI::WebView* webView);

		/**
		 * Destructor.
		 */
		virtual ~PhoneGapMessageHandler();

		/**
		 * Implementation of PhoneGap and other APIs exposed in JavaScript.
		 * This function is used to detect different messages and call the
		 * respective function in MoSync.
		 *
		 * @return true if message was handled, false if not.
		 */
		bool PhoneGapMessageHandler::handlePhoneGapMessage(JSONMessage& message);

		/**
		 * Called whenever sensor data is ready
		 */
		void sensorEvent(MASensor sensorData);

		/**
		 * Initializes PhoneGap by sending the native Ready Message.
		 */
		void initializePhoneGap();

		/**
		 * Set the sound resource played as the beep sound.
		 */
		void setBeepSound(MAHandle sound);

		/**
		 * Handles location events generated by the location API.
		 */
		virtual void customEvent(const MAEvent&);

		/**
		 * General wrapper for phoneGap error callback.
		 * If an operation is successful this function should be called.
		 *
		 * @param data the data that should be passed to the callback function
		 */
		void sendConnectionType(MAUtil::String callbackID);

		/**
		 * Hardware Listeners and Hardware Access is initialized in this function.
		 */
		void enableHardware();

		/**
		 * Sends Device's information to PhoneGap's JavaScript Instance
		 *
		 * @param callbackID ID of the PhoneGapCallback to be used
		 */
		void sendDeviceProperties(MAUtil::String callbackID);

		/**
		 * Processes the Key Events and sends the appropriate
		 * message to PhoneGap.
		 */
		void processKeyEvent(int keyCode, int nativeKeyCode);

		/**
		 * Call the PhoneGap success function.
		 *
		 * @param callbackID The id of the JS callback function.
		 * @param status Status code.
		 * @param args Return values as a JSON string.
		 * @param keepCallback true if this callback should be kept by PhoneGap.
		 * @param castFunction Name of an optional JS function that
		 * will convert the JSON args to a JS object.
		 */
		void callSuccess(
			const MAUtil::String& callbackID,
			const MAUtil::String& status,
			const MAUtil::String& args,
			bool keepCallback = false,
			const MAUtil::String& castFunction = ""
			);

		/**
		 * Call the PhoneGap error function.
		 *
		 * @param callbackID The id of the JS callback function.
		 * @param errorCode The error code.
		 * @param errorMessage Optional error message.
		 * @param keepCallback true if this callback should be kept by PhoneGap.
		 */
		void PhoneGapMessageHandler::callError(
			const MAUtil::String& callbackID,
			const MAUtil::String& errorCode,
			const MAUtil::String& errorMessage = "",
			bool keepCallback = false
			);

		/**
		 * Evaluate a callback function in JavaScript.
		 *
		 * @param callbackFunction The JS function to handle the callback.
		 * @param status Status code.
		 * @param callbackID The id of the JS callback.
		 * @param args Result values as a JSON string.
		 * @param keepCallback true if this callback should be kept by PhoneGap.
		 * @param castFunction Name of an optional JS function that
		 * will convert the JSON args to a JS object.
		 */
		void PhoneGapMessageHandler::callCallback(
			const MAUtil::String& callbackFunction,
			const MAUtil::String& callbackID,
			const MAUtil::String& status,
			const MAUtil::String& args,
			bool keepCallback = false,
			const MAUtil::String& castFunction = ""
			);

		/**
		 * Evaluate JavaScript code in the WebView.
		 *
		 * @param script Code that should be evaluated.
		 */
		void callJS(const MAUtil::String& script);

		/**
		 * Set the target class for sensor event messages.
		 * @param sensor The sensor that is configured.
		 * @param toSensorManager If true, the SensorManager object will receive the events, normal PhoneGap API if false
		 */
		void setSensorEventTarget(int sensor, bool toSensorManager);

	private:
		/**
		 * The WebView used by PhoneGap.
		 */
		NativeUI::WebView* mWebView;

		/**
		 * PhoneGap sensor API:s message handler.
		 */
		PhoneGapSensors mPhoneGapSensors;

		/**
		 * W3C sensor manager API:s message handler.
		 */
		SensorManager mPhoneGapSensorManager;

		/**
		 * PhoneGap File API message handler.
		 */
		PhoneGapFile mPhoneGapFile;

		/**
		 * PhoneGap Capture API message handler.
		 */
		PhoneGapCapture mPhoneGapCapture;

		/**
		 * PhoneGap Camera API message handler.
		 */
		PhoneGapCamera mPhoneGapCamera;

		/**
		 * Notification API message handler.
		 */
		PushNotificationManager mPushNotificationManager;

		/**
		 * The beep sound.
		 */
		MAHandle mBeepSound;

		/**
		 * Controls where each sensor event is delivered.
		 */
		bool mSensorEventToManager[MAXIMUM_SENSORS];
	};
} // namespace

#endif

/*! @} */
