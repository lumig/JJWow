// AFNetworkActivityIndicatorManager.h
// Copyright (c) 2011–2016 Alamofire Software Foundation ( http://alamofire.org/ )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

#import <TargetConditionals.h>

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 `AFNetworkActivityIndicatorManager` manages the state of the network activity indicator in the status bar. When enabled, it will listen for notifications indicating that a session task has started or finished, and start or stop animating the indicator accordingly. The number of active requests is incremented and decremented much like a stack or a semaphore, and the activity indicator will animate so long as that number is greater than zero.

 You should enable the shared instance of `AFNetworkActivityIndicatorManager` when your application finishes launching. In `AppDelegate application:didFinishLaunchingWithOptions:` you can do so with the following code:

    [[AFNetworkActivityIndicatorManager sharedManager] setEnabled:YES];

 By setting `enabled` to `YES` for `sharedManager`, the network activity indicator will show and hide automatically as requests start and finish. You should not ever need to call `incrementActivityCount` or `decrementActivityCount` yourself.

 See the Apple Human Interface Guidelines section about the Network Activity Indicator for more information:
 http://developer.apple.com/library/iOS/#documentation/UserExperience/Conceptual/MobileHIG/UIElementGuidelines/UIElementGuidelines.html#//apple_ref/doc/uid/TP40006556-CH13-SW44
 */
//这个宏的意思指下边的类不能被扩展
NS_EXTENSION_UNAVAILABLE_IOS("Use view controller based solutions where appropriate instead.")
@interface AFNetworkActivityIndicatorManager : NSObject

/**
 A Boolean value indicating whether the manager is enabled.

 If YES, the manager will change status bar network activity indicator according to network operation notifications it receives. The default value is NO.
 是否显示状态栏菊花轮
 */
@property (nonatomic, assign, getter = isEnabled) BOOL enabled;

/**
 A Boolean value indicating whether the network activity indicator manager is currently active.
  这个属性用来获取和设置激活状态。这个属性支持kvo。如果是设置，首先回调用自己实现的控制转态的block，如果没有实现这个block，就直接通过UIApplication来设置激活状态了。
*/
@property (readonly, nonatomic, assign, getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible;

/**
 A time interval indicating the minimum duration of networking activity that should occur before the activity indicator is displayed. The default value 1 second. If the network activity indicator should be displayed immediately when network activity occurs, this value should be set to 0 seconds.
 
 Apple's HIG describes the following:

 > Display the network activity indicator to provide feedback when your app accesses the network for more than a couple of seconds. If the operation finishes sooner than that, you don’t have to show the network activity indicator, because the indicator is likely to disappear before users notice its presence.
激活延时，指的是当网络开始到显示激活的一个时间间隔。默认的是1秒，为什么要设置这个呢？根据人机交互指南，有些网络很快，这个情况就不需要显示激活的那个状态了。
 */
@property (nonatomic, assign) NSTimeInterval activationDelay;

/**
 A time interval indicating the duration of time of no networking activity required before the activity indicator is disabled. This allows for continuous display of the network activity indicator across multiple requests. The default value is 0.17 seconds.
  状态消失的延时，默认为0.17秒。
 */

@property (nonatomic, assign) NSTimeInterval completionDelay;

/**
 Returns the shared network activity indicator manager object for the system.

 @return The systemwide network activity indicator manager.
 */
+ (instancetype)sharedManager;

/**
 Increments the number of active network requests. If this number was zero before incrementing, this will start animating the status bar network activity indicator.
 增加激活的请求的数量，当数量大于0，就处于激活状态。
 */
- (void)incrementActivityCount;

/**
 Decrements the number of active network requests. If this number becomes zero after decrementing, this will stop animating the status bar network activity indicator.
 减少数量。
 */
- (void)decrementActivityCount;

/**
 Set the a custom method to be executed when the network activity indicator manager should be hidden/shown. By default, this is null, and the UIApplication Network Activity Indicator will be managed automatically. If this block is set, it is the responsiblity of the caller to manager the network activity indicator going forward.

 @param block A block to be executed when the network activity indicator status changes.
 根据状态来自定义事件
 */
- (void)setNetworkingActivityActionWithBlock:(nullable void (^)(BOOL networkActivityIndicatorVisible))block;

@end

NS_ASSUME_NONNULL_END

#endif
