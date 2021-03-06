package com.mosync.pim;

import static com.mosync.internal.android.MoSyncHelpers.DebugPrint;
import android.content.ContentResolver;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_ERR_NONE;

import static com.mosync.internal.generated.IX_PIM.MA_PIM_FIELD_CONTACT_CLASS;
import static com.mosync.internal.generated.IX_PIM.MA_PIM_TYPE_INT;

public class PIMFieldClass extends PIMField {

	/**
	 * Constructor
	 */
	public PIMFieldClass() {
		mType = MA_PIM_FIELD_CONTACT_CLASS;
		mDataType = MA_PIM_TYPE_INT;
	}

	void createMaps() {

	}

	void read(ContentResolver cr, String contactId) {
		print();
	}

	int checkForPreferredAttribute(int index) {
		return 0;
	}

	int getAndroidAttribute(int index) {
		return 0;
	}

	int setAttribute(int index, int attribute) {
		return MA_PIM_ERR_NONE;
	}

	char[] getLabel(int index) {
		return null;
	}

	void setLabel(int index, String label) {
	}

	boolean hasCustomLabel(int index) {
		return false;
	}

	char[] getData(int index) {
		return null;
	}

	void setData(int index, char[] buffer) {
	}

	boolean isSupported() {
		return false;
	}

	/**
	 * Print field values.
	 */
	void print() {
		DebugPrint("***********CLASS***********");
		DebugPrint("Not supported");
		DebugPrint("***************************");
	}
}
