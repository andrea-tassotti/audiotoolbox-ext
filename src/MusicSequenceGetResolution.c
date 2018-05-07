/*!
 *  @header MusicSequenceGetResolution.c
 *  @abstract   Implementation of MusicSequenceGetResolution function.
 *  @discussion 
 *				
 */
#include <AudioToolbox/MusicPlayer.h>

/*!
 *	@function
 *  @abstract   Get sequence time resolution 
 *  @discussion Get time resolution (PPQ) from sequence properties
 *				or set default 480.
 *				Resolution is a read-only SInt16 value that is 
 *				valid only for a tempo track.
 *	@copyright	Andrea Tassotti
 */
OSStatus MusicSequenceGetResolution(MusicSequence inSequence, SInt16 *outResolution)
{
	MusicTrack tempoTrack;
	
	OSStatus status = MusicSequenceGetTempoTrack(inSequence, &tempoTrack);
	if (status != noErr)	return status;
	
	UInt32 ioLength = sizeof(SInt16);
	status = MusicTrackGetProperty (
								  tempoTrack,
								  kSequenceTrackProperty_TimeResolution,
								  outResolution,
								  &ioLength
								  );
	// Default
	if (status != noErr)
	{
		*outResolution = 480;
		status = 0;
	}
	
	return status;
}


