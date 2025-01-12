//
// BBRtcVideoFrame.h
//
// Copyright (c) 2021 banban. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The protocol of the raw video data.

 @note This protocol applies to iOS only.
 */
@protocol BBRtcVideoDataFrameProtocol <NSObject>
@required

/** Gets the video data captured by the local camera.

 @since v3.4.5

 After you successfully register the raw video frame protocol, the SDK triggers
 this callback each time a video frame is received. You can get the video data
 captured by the local camera in `videoFrame` and then process the video data
 according to your scenario. After processing, you can use `videoFrame` to pass
 the processed video data back to the SDK.

 **Note**:

 - This callback applies to iOS only.
 - If you get the video data in RGBA color encoding format, Aopa does not
 support using this callback to send the processed data in RGBA color encoding
 format back to the SDK.
 - The video data obtained through this callback has not undergone
 preprocessing, such as watermarking, cropping content, rotating, or
 image enhancement.

 @param videoFrame The video frame. See AopaVideoDataFrame.

 @return - YES: If the video frame processing fails, the video frame is not
 passed back to the SDK.
 - NO: If the video frame processing fails, the video frame is still passed
 back to the SDK.
 */
- (BOOL)onCaptureVideoFrame:(BBRtcVideoFrame*)frame;
/** Gets the local pre-encoded video data.

 @since v3.4.5

 After you successfully register the raw video frame protocol and use
 [getObservedFramePosition]([AopaVideoDataFrameProtocol getObservedFramePosition])
 to set the observation `AopaVideoFramePositionPreEncoder (1 << 2)`, the SDK
 triggers this callback each time a video frame is received. You can get the
 local pre-encoded video data in `videoFrame` and then process the video data
 according to your scenario. After processing, you can use videoFrame to pass
 the processed video data back to the SDK.

 **Note**:

 - This callback applies to iOS only.
 - If you get the video data in RGBA color encoding format, Aopa does not
 support using this callback to send the processed data in RGBA color encoding
 format back to the SDK.
 - The video data obtained through this callback has not undergone
 preprocessing, such as watermarking, cropping content, rotating, or
 image enhancement.

 @param videoFrame The video frame. See AopaVideoDataFrame.

 @return - YES: If the video frame processing fails, the video frame is not
 passed back to the SDK.
 - NO: If the video frame processing fails, the video frame is still passed
 back to the SDK.
 */
- (BOOL)onPreEncodeVideoFrame:(BBRtcVideoFrame*)frame;
/** Gets the incoming remote video data.

 @since v3.4.5

 After you successfully register the raw video frame and set the return value
 of [isMultipleChannelFrameWanted]([AopaVideoDataFrameProtocol isMultipleChannelFrameWanted])
 as `NO`, the SDK triggers this callback each time a video frame is received.
 You can get the incoming remote video data in `videoFrame` and then process
 the video data according to your scenario. After processing, you can use
 `videoFrame` to pass the processed video data back to the SDK.

 **Note**:

 - This callback applies to iOS only.
 - If you get the video data in RGBA color encoding format, Aopa does not
 support using this callback to send the processed data in RGBA color
 encoding format back to the SDK.

 @param videoFrame The video frame. See AopaVideoDataFrame.
 @param uid The user ID of the remote user.

 @return - YES: If the video frame processing fails, the video frame is not
 passed back to the SDK.
 - NO: If the video frame processing fails, the video frame is still passed
 back to the SDK.
 */
- (BOOL)onRenderVideoFrame:(BBRtcVideoFrame*)frame forUid:(unsigned int)uid;
/** Sets the format of the raw video data output by the SDK.

 @since v3.4.5

 If you want to get raw video data in a color encoding format other than YUV
 420, you need to implement the `getVideoFormatPreference` callback in
 AopaVideoDataFrameProtocol. After you successfully register the raw video
 frame protocol, the SDK triggers this callback each time a video frame is
 received. You need to set the desired color encoding format of the video
 data in the return value of this callback.

 @note This callback applies to iOS only.

 @return The color encoding format of the raw video data output by the SDK.
 See AopaVideoFrameType.
 */
- (BBRtcVideoFrameType)getVideoFormatPreference;
/** Sets whether to rotate the raw video data output by the SDK.

 @since v3.4.5

 If you want to get raw video data that has been rotated according to the
 value of `rotation` in AopaVideoDataFrame, you need to implement the
 `getRotationApplied` callback in AopaVideoDataFrameProtocol. After you
 successfully register the raw video frame protocol, the SDK triggers this
 callback each time a video frame is received. You need to set whether to
 rotate the observed raw video data in the return value of this callback.

 **Note**:

 - This callback applies to iOS only.
 - This function supports video data in RGBA and YUV 420 color encoding
 formats only.

 @return Whether to rotate the raw video data output by the SDK:

 - YES: Rotate the raw video data.
 - NO: (Default) Do not rotate the raw video data.
 */
- (BOOL)getRotationApplied;
/** Sets whether to mirror the raw video data output by the SDK.

 @since v3.4.5

 If you want to get the mirrored raw video data, you need to implement the
 `getMirrorApplied` callback in AopaVideoDataFrameProtocol. After you
 successfully register the raw video frame observer, the SDK triggers this
 callback each time a video frame is received. You need to set whether to
 mirror the observed raw video data in the return value of this callback.

 **Note**:

 - This callback applies to iOS only.
 - This function supports video data in RGBA and YUV 420 color encoding
 formats only.

 @return Whether to mirror the raw video data output by the SDK:

 - YES: Mirror the raw video data.
 - NO: (Default) Do not mirror the raw video data.
 */
- (BOOL)getMirrorApplied;
/** Sets the video observation positions.

 @since v3.4.5

 After you successfully register the raw video frame observer, the SDK uses
 the `getObservedFramePosition` callback to determine at each specific
 video-frame processing node whether to trigger the following callbacks:

 - [onCaptureVideoFrame]([AopaVideoDataFrameProtocol onCaptureVideoFrame:])
 - [onPreEncodeVideoFrame]([AopaVideoDataFrameProtocol onPreEncodeVideoFrame:])
 - [onRenderVideoFrame]([AopaVideoDataFrameProtocol onRenderVideoFrame:forUid:]) or
 [onRenderVideoFrameEx]([AopaVideoDataFrameProtocol onRenderVideoFrameEx:forUid:inChannel:])

 You can set the position or positions that you want to observe by modifying
 the return value of `getObservedFramePosition` according to your scenario.

 **Note**:

 - This callback applies to iOS only.
 - To observe multiple positions, use `|` (the OR operator).
 - The default return value of this callback is
 `AopaVideoFramePositionPostCapture (1 << 0)` and
 `AopaVideoFramePositionPreRenderer (1 << 1)`.
 - To conserve system resources of the device, you can reduce the number of
 observation positions appropriately according to your scenario.

 @return The bit mask of the observation positions. See AopaVideoFramePosition.
 */
- (BBRtcVideoFramePosition)getObservedFramePosition;

/** Sets whether the SDK outputs remote video data received in multiple channels.

 @since v3.4.5

 In a multi-channel (AopaRtcChannel) scenario, if you want to get the remote
 video data received in multiple channels, you need to implement the
 `isMultipleChannelFrameWanted` callback in AopaVideoDataFrameProtocol and
 set the return value of this callback to `YES`. The SDK triggers the
 [onRenderVideoFrameEx]([AopaVideoDataFrameProtocol onRenderVideoFrameEx:forUid:inChannel:])
 callback each time a video frame is received, from which you can get the
 expected multi-channel video data.

 **Note**:

 - This callback applies to iOS only.
 - The SDK chooses to trigger either the
 [onRenderVideoFrame]([AopaVideoDataFrameProtocol onRenderVideoFrame:forUid:]) or
 [onRenderVideoFrameEx]([AopaVideoDataFrameProtocol onRenderVideoFrameEx:forUid:inChannel:])
 callback depending on the return value that you set in the
 `isMultipleChannelFrameWanted` callback. Aopa recommends that you set the
 return value as `YES` in a multi-channel scenario.

 @return Whether the SDK outputs remote video data received in multiple channels:

 - YES: The SDK uses `onRenderVideoFrameEx` to output remote video data
 received in multiple channels.
 - NO: (Default) The SDK uses `onRenderVideoFrame` to output remote video data
 received in a single channel.
 */
- (BOOL)isMultipleChannelFrameWanted;

/** Gets the remote video data received in multiple channels.

 @since v3.4.5

 After you successfully register the raw video frame protocol and set the
 return value of
 [isMultipleChannelFrameWanted]([AopaVideoDataFrameProtocol isMultipleChannelFrameWanted])
 as `YES`, the SDK triggers this callback each time a video frame is received.
 You get the remote video data received in multiple channels in `videoFrame`
 and then process the video data according to your scenario. After processing,
 you can pass the processed video data back to the SDK.

 **Note**:

 - This callback applies to iOS only.
 - If you get the video data in RGBA color encoding format, Aopa does not
 support using this callback to send the processed data in RGBA color encoding
 format back to the SDK.

 @param videoFrame The video frame. See AopaVideoDataFrame.
 @param uid The user ID of the remote user.
 @param channelId The channel name.

 @return - YES: If the video frame processing fails, the video frame is not
 passed back to the SDK.
 - NO: If the video frame processing fails, the video frame is still passed
 back to the SDK.
 */
- (BOOL)onRenderVideoFrameEx:(BBRtcVideoFrame*)frame forUid:(unsigned int)uid inChannel:(NSString*)channelId;

@end
