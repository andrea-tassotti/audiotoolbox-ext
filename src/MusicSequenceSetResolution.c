/*!
    @header MusicSequenceSetResolution.c
    @abstract   <#abstract#>
    @discussion <#description#>
*/

#include <AudioToolbox/MusicPlayer.h>

/*!
 *	@abstract	 Workaround to change MusicSequence resolution.
 * 	@discussion	MusicSequence property kSequenceTrackProperty_TimeResolution is read-only: resolution can be set for file and rea from file.
 */
OSStatus MusicSequenceSetResolution(MusicSequence *inSequence, UInt16 ppq){
	OSStatus err;	
	CFDataRef tempData;

	err = MusicSequenceFileCreateData (
									   *inSequence,
									   kMusicSequenceFile_MIDIType,
									   0,
									   ppq,
									   &tempData
									   );
	if (err != noErr )
		return err;

	DisposeMusicSequence(*inSequence);


	err = MusicSequenceFileLoadData (
									 *inSequence,
									 tempData,
									 kMusicSequenceFile_MIDIType,
									 0
									 );
	
	CFRelease(tempData);
	
	return err;
}
