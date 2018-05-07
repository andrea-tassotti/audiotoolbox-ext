/*!
    @header MusicSequenceGetOverallLength.c
    @abstract   Implementation of MusicSequenceGetOverallLength function.
    @discussion <#description#>
*/
#include <AudioToolbox/MusicPlayer.h>

/*!
    @function
    @abstract   Get sequence overall length
    @discussion Get length of longest track
    @param      inSequence 	Input sequence
    @param      outSequenceLength 	Sequence length
    @result     error
 	@copyright	Andrea Tassotti
*/
OSStatus MusicSequenceGetOverallLength(	MusicSequence inSequence,
										MusicTimeStamp * outSequenceLength )
{
	UInt32 ntracks;
	OSStatus err;
	
	if ( !outSequenceLength )
		return -50;
		
	*outSequenceLength = 0;

	if ( (err = MusicSequenceGetTrackCount (inSequence, &ntracks)) != noErr )
		return err;

	for (UInt32 i = 0; i < ntracks; ++i)
	{
		MusicTrack track;
		MusicTimeStamp trackLength;
		UInt32 propsize = sizeof(MusicTimeStamp);

		if ( (err = MusicSequenceGetIndTrack(inSequence, i, &track)) != noErr )
			return err;
		
		if ( (err = MusicTrackGetProperty(track, kSequenceTrackProperty_TrackLength,
								   &trackLength, &propsize)) != noErr )
			return err;

		if ( trackLength > *outSequenceLength)
			*outSequenceLength = trackLength;
	}

	// No API to update MusicSequence metadata
	return noErr;
}
