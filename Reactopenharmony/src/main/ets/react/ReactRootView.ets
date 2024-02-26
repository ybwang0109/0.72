import hilog from '@ohos.hilog';
import UIAbility from '@ohos.app.ability.UIAbility';
import { ReactInstanceManager } from "./ReactInstanceManager"
import { ReactRoot } from "./ReactRoot"

export class ReactRootView implements ReactRoot{
  private mAbility:UIAbility; //todo:这个参数在OpenHarmony上可能没有用，如果真的没有用，需要删除掉
  private mRootViewTag: number = 101;
  private mReactInstanceManager:ReactInstanceManager | null = null;
  private mJSModuleName: string = '';
  private mAppProperties: string = '';
  private mWasMeasured: boolean = false;
  private mIsAttachedToInstance: boolean = false;
  private mLastWidth: number = 0;
  private mLastHeight: number = 0;
  private mLastOffsetX: number = 0;
  private mLastOffsetY: number = 0;

  STATE_STARTED: number = 1;
  STATE_STOPPED: number = 0;
  private mState: number = this.STATE_STOPPED;

  private readonly TAG: string = "ReactRootView"

  constructor(Ability: UIAbility) {
	this.mAbility = Ability;
  }

  onStage(stage: number): void {
	this.onAttachedToReactInstance();
  }

  getAppProperties(): string {
	return this.mAppProperties;
  }

  getJSModuleName(): string {
	return this.mJSModuleName;
  }

  getWidthMeasureSpec(): number {
	return this.mLastWidth;
  }

  getHeightMeasureSpec(): number {
	return this.mLastHeight;
  }

  public getState(): number {
	return this.mState
  }

  getRootViewTag(): number{
	return this.mRootViewTag;
  }

  public onAttachedToReactInstance(): void {
  // 注册处理JSTouch事件
  }

  /**
   * Schedule rendering of the react component rendered by the JS application from the given JS
   * module (@{param moduleName}) using provided {@param reactInstanceManager} to attach to the JS
   * context of that manager. Extra parameter {@param launchOptions} can be used to pass initial
   * properties for the react component.
   */
  public startReactApplication(
	reactInstanceManager: ReactInstanceManager,
	moduleName: string,
	initialProperties: string): void {

	hilog.info(0x0000, this.TAG, '%{public}s', 'startReactApplication');
	this.mReactInstanceManager = reactInstanceManager;
	this.mJSModuleName = moduleName;
	this.mAppProperties = initialProperties;

	this.mReactInstanceManager.createReactContextInBackground();
	/** 这里没有挂载RootView实例给InstanceManager，当RootView完成第一次测量后执行实例挂载，下面的特性支持提前挂载RootView **/

	// if in this experiment, we initialize the root earlier in startReactApplication
	// instead of waiting for the initial measure
	// if (ReactFeatureFlags.enableEagerRootViewAttachment) {
	//   if (!mWasMeasured) {
	//     // Ideally, those values will be used by default, but we only update them here to scope
	//     // this change to `enableEagerRootViewAttachment` experiment.
	//     setSurfaceConstraintsToScreenSize();
	//   }
	//   attachToReactInstanceManager();
	// }
  }

  public onAreaChange(oldValue: Area, newValue: Area) {

	this.mLastWidth = newValue.width as number;
	this.mLastHeight = newValue.height as number
	this.mLastOffsetX = newValue.globalPosition.x as number
	this.mLastOffsetY = newValue.globalPosition.y as number

	this.mWasMeasured = true;

	// Check if we were waiting for onMeasure to attach the root view.
	if (this.hasActiveReactInstance() && !this.isViewAttachedToReactInstance()) {
	  this.attachToReactInstanceManager();
	} else if (this.mLastWidth != oldValue.width || this.mLastHeight != oldValue.height) {
	  this.updateRootLayoutSpecs(this.mLastWidth, this.mLastHeight);
	}
  }

  private attachToReactInstanceManager(): void {
	if (this.mIsAttachedToInstance) {
	  return;
	}
	this.mIsAttachedToInstance = true;



	this.mReactInstanceManager?.attachRootView(this);
	//todo:待增加监听全局Layout事件能力
  }



  private updateRootLayoutSpecs(width: number, height: number): void {

  }

  public onAboutToAppear(): void{

  }
  public onAboutToDisappear(): void{

  }

  public hasActiveReactInstance(): boolean {
	return this.mReactInstanceManager != null;
  }

  public isViewAttachedToReactInstance(): boolean {
	return this.mIsAttachedToInstance;
  }
}