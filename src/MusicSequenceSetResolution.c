/*!
    @header MusicSequenceSetResolution.c
    @abstract   Implementation of MusicSequenceSetResolution function.
    @discussion 
*/
#include <AudioToolbox/MusicPlayer.h>

/*!
 *	@function
 *	@abstract	 Workaround to change MusicSequence resolution.
 * 	@discussion	MusicSequence property kSequenceTrackProperty_TimeResolution is read-only: resolution can be set for file and rea from file.
 *
 *	@copyright Andrea Tassotti
 */
OSStatus MusicSequenceSetResolution(MusicSequence inSequence, SInt16 ppq){
	OSStatus err;	
	CFDataRef tempData;
	UInt32 ntracks;
	
	MusicSequenceGetTrackCount (inSequence, &ntracks);
	if ( ntracks > 0 )
	{
		fprintf(stderr, "MusicSequenceSetResolution: sequence *must* be empty: sequence has %i track(s)\n", ntracks);
		return -50;
	}

	err = MusicSequenceFileCreateData (
									   inSequence,
									   kMusicSequenceFile_MIDIType,
									   0,
									   ppq,
									   &tempData
									   );
	if (err != noErr )
		return err;


	err = MusicSequenceFileLoadData (
									 inSequence,
									 tempData,
									 kMusicSequenceFile_MIDIType,
									 0
									 );
	
	CFRelease(tempData);
	
	return err;
}
