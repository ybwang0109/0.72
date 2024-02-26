import ArrayList from '@ohos.util.ArrayList';
import { ReactViewManager } from './view/ReactViewManager'
import { ReactParagraphManager } from './text/ReactParagraphManager';
import { ReactScrollViewManager } from './scroll/ReactScrollViewManager';
import { view_manager } from 'libreact_arkui.so';

export function createViewManagers(): ArrayList<view_manager> {
  const ViewManagers: ArrayList<view_manager> = new ArrayList<view_manager>();

  ViewManagers.add(new ReactViewManager());
  ViewManagers.add(new ReactParagraphManager());
  ViewManagers.add(new ReactScrollViewManager());

  return ViewManagers;
}