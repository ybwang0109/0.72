// 
// Created on 2024/2/4.
// 
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native _api.h".

#include "fabric mounting_manager.h"

namespace rnoh {
    fabric_mounting_manager::fabric_mounting_manager() {
        LOG(ERROR) << "fabric_mounting manager::fabric_mounting_ manager begin. this is " << this << "\n";
    }
    
    void fabric_mounting_manager::bindingArkTsParty(aki::Value arkTs) {
        LOG(ERROR) << "fabric_mounting_manager::bindingArkTsParty. this is " <<this << "\n";
        arkTsThis_ = arkTS;
    }

    void fabric_mounting_manager::onSurfacestart(SurfaceId surfaceId, Surface_mounting_manager *Surface_manager) {
        LOG(ERROR) << "fabric_mounting_manager::onSurfaceStart this is " << this << "\n";
        LOG(ERROR) << "fabric_mounting_manager::onSurfaceStart Surfaceld = " << SurfaceId <<  "\n";

        LOG (ERROR) << "fabric_mounting_manager::onSurfacestart surface_mounting_manager = " << Surface_manager <<  "\n";
        allocatedViewRegistry_.emplace(surfaceId, facebook::butter::set<facebook::react::Tag>{});
        surfaceMountingManagerByID_.insert_or_assign(surfaceId, surface_manager);
    }

    void fabric_mounting_manager::preallocateShadowiew(Surfaceld surfaceld, Shadowiew const &shadowView) {

        LOG(ERROR) << "fabric_mounting_manager::preallocateShadowView begin. surfaceld: " << surfaceId << "\n";
        {
            // std::lock_guard lock(allocatedViewsMutex_); //todo;
            auto allocatedviewsIterator = allocatedViewRegistry_.find(surfaceId);
            if (allocatedViewsIterator == allocatedViewRegistry_.end()) {
                return;
            }
            auto &allocatedViews = allocatedViewsIterator->second;
            if (allocatedViews.find(shadowView.tag) != allocatedViews.end()) {
                return;
            }
            allocatedViews.insert(shadowView.tag);
        }

        bool isLayoutableShadowNode = shadowView.layoutMetrics != facebook::react::EmptyLayoutMetrics;

        surface_mounting_manager *surfaceMountingManager = getSurfaceManager(surfaceId);

        taskExecutor->runTask(TaskThread::MAIN, [this, surfaceMountingManager, Tag = shadowView.tag,
                                                 componentName = shadowView.componentName,
                                                 Props = shadowView.props->rawProps, state = shadowView.state,
                                                 eventEmitter = shadowView.eventEmitter, isLayoutableshadowNode] {
            surfaceMountingManager->preallocateView(Tag, componentName, Props, state, eventEmitter,
                                                    isLayoutableShadowNode);
        });
        LOG(ERROR) << "fabric mounting manager::preallocateshadowView end. surfaceld: " << surfaceld << "\n"
    }

    void fabric_mounting_manager::executeMount (MountingCoordinator::Shared mountingCoordinator) {
        LOG(ERROR) << "fabric_mounting_manager::executeMount begin.";

        auto mountingTransaction = mountingCoordinator->pullTransaction();

        if (!mountingTransaction.has_value()) {
            LOG(ERROR) << "fabric mounting _manager::executeMount return. ";
            return;
        }

        auto surfaceld = mountingTransaction->getSurfaceId();
        auto &mutations = mountingTransaction->getMutations();
        LOG(ERROR) << "mutation surfaceld=" << surfaceId;
        {
            std::lock_guard allocatedViewsLock(allocatedViewsMutex_);
            auto allocatedViewsIterator = allocatedViewRegistry_.find(surfaceld);
            auto const &allocatedViewTags = allocatedViewsIterator != allocatedViewRegistry_.end()
                                                ? allocatedViewsIterator->second
                                                :butter::set<Tag>{};
            if (allocatedViewsIterator == allocatedViewRegistry_.end()) {
                LOG(ERROR) << "Executing commit after surface was stopped!";
            }

            surface_mounting_manager *surfaceMountingManager = getSurfaceManager (surfaceId);

            for (const auto &mutation : mutations) {
                const auto &parentShadowView = mutation.parentShadowView;
                const auto &oldchildShadowView = mutation.oldchildShadowView;
                const auto &newChildShadowView = mutation.newChildShadowView;
                auto &mutationType = mutation.type;
                auto &index = mutation.index;

                bool isLayoutableShadowNode = newChildShadowView.layoutMetrics != facebook::react::EmptyLayoutMetrics;
                bool isVirtual = mutation.mutatedviewIsVirtual();
                switch (mutationType) {
                case ShadowViewMutation::Create: {
                    LOG(ERROR) << "mutation.Create Tag=" << mutation.newChildShadowView.tag << " "
                               << mutation.newChildShadowView.props->rawProps;
                    bool shouldcreateview = !allocatedViewTags.contains(newChildShadowView.tag);

                    if (shouldcreateview) {
                        taskExecutor->runTask(
                            TaskThread::MAIN,
                            [this, surfaceMountingManager, Tag = newChildShadowView.tag,
                            componentName = newChildShadowView.componentName,
                            Props = newChildShadowView.props->rawProps, state = newChildShadowView.state,
                            eventEmitter = newChildShadowiew.eventEmitter, isLayoutableShadowNode] {
                                surfaceMountingManager->createview (Tag, componentName, Props, State, eventEmitter,
                                                                    isLayoutableShadowNode);
                            });
                    }
                    break;
                }
                case ShadowViewMutation::Remove: {
                    LOG(ERROR) << "mutation.Remove childTag=" << mutation.oldchildshadowView.tag
                               << "parentTag="<< mutation.parentShadowView.tag;
                    taskExecutor->runTask(TaskThread::MAIN, [this, surfaceMountingManager, Tag = oldChildShadowView.tag,
                                                             parentTag = parentShadowView.tag, index]  {
                        surfaceMountingManager->removeViewAt(Tag, parentTag, index);
                    });
                }
                case ShadowViewMutation::RemoveDeleteTree: {
                    taskExecutor->runTask(TaskThread::MAIN, [this, surfaceMountingManager, Tag = oldChildShadowView.tag,
                                                             parentTag = parentShadowView.tag, index] {
                        surfaceMountingManager->removeDeleteTreeAt(Tag, parentTag, index);
                    });
                }
                case ShadowViewMutation::Delete: {
                    LOG(ERROR) << "mutation. Delete Tag-" << MUTATION.oldChildShadowView.tag 
                    taskExecutor->runTask(TaskThread::MAIN,
                                          [this, surfaceMountingManager, Tag = oldChildShadowView.tag] {
                                              surfaceMountingManager->deleteView(Tag);
                                          });
                }
                case ShadowViewMutation::Update: {
                    LOG(ERROR) << "mutation.Update Tag=" << mutation.newChildShadowView.tag << " "
                                << mutation.newChildShadowView.props->rawProps;
                }
                case ShadowViewMutation::Insert: {
                    LOG(ERROR) << "mutation.Insert childTag=" << mutation.newChildShadowView.tag
                                << "parentTag="<< mutation.parentShadowView.tag << " index= " << mutation.index;
                    if (!isVirtual) {
                        // Insert item
                        taskExecutor->runTask(TaskThread::MAIN,
                                                [this, surfaceMountingManager, Tag = newChildShadowView.tag,
                                                parentTag = parentShadowView.tag,
                                                index] { surfaceMountingManager->addViewAt (parentTag, Tag, index); });

                        //                          bool allocationCheck
                        //                              allocatedViewTags.find(newChildShadowView.tag) ==
                        //                              allocatedViewTags.end();
                        //                          bool shouldcreateview = allocationCheck;
                        //                          if (shouldcreateView) {
                        //                              cppUpdatePropsMountItems.push backl
                        //                                  CppMountItem::UpdatePropsMountItem({}, newChildshadowView));
                        //                          }
                        // 
                        //                          // State
                        //                          if (newChildShadowView.state){
                        //                              cppupdateStateMountItems.push_back(CppMountItem::UpdatestateMountItem(newchildshadowView));
                        //                          }
                        //
                        //                          // Padding: padding mountItems must be executed before layout props 
                        //                          //are updated in the view. This is necessary to ensure that events
                        //                          // (resulting from layout changes) are dispatched with the correct 
                        //                          // padding information.
                        //                          if (newChildShadowView.layoutMetrics.contentInsets!=
                        //                          EdgeInsets::ZERO) {
                        //                              cppUpdatePaddingMountItems.push_back(
                        //                                  CppMountItem::UpdatePaddingMountItem(newChildShadowView));
                        //                          }
                        // 
                        //                          // Layout
                        //                          cppupdateLayoutMountItems.push _back(
                        //                              CppMountItem::UpdateLayoutMountItem(newChildShadowView,
                        //                              parentshadowView));
                        //
                        //                          // OverflowInset: This is the values indicating boundaries including
                        //                          // children of the current view. The layout of current view may not
                        //                          // change, and we separate this part from layout mount items to not 
                        //                          // pack too much data there.
                        //                          if (newChildShadowView.layoutMetrics.overflowInset !=
                        //                          EdgeInsets::ZERO) {
                        //                              cppUpdateOverflowInsetMountItems.push_back(
                        //                                  CppMountItem::UpdateOverflowInsetMountItem(newChildShadowView));
                        //                           }
                        //                         }  

                        //                          // EventEmitter
                        //                          cppUpdateEventEmitterMountItems.push_back(
                        //                              CppMountItem::UpdateEventEmitterMountItem(mutation.newChildshadowView));
                        
                        break;
                    }
                }
                }

                if (allocatedViewsIcerator != allocatedViewRegistry_.end()) {
                    auto &views = allocatedViewsIterator->second;
                    for (auto const &mutation : mutations) {
                        switch (mutation.type) {
                        case ShadowViewMutation::Create:
                            views.insert (mutation.newChildShadowView.tag);
                            break;
                        case ShadowViewMutation::Delete:
                            views.erase(mutation.oldchildShadowView.tag);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
        LOG (ERROR) << "fabric_mounting_manager::executeMount end. ";
    }

       /*
        mutation surfaceld=1
        mutation.Update Tag=1 {}
        mutation.Create Tag=46 {"snapToEnd":true,"flexGrow":1,"onLayout":true,"overflow":"scroll","snapToStart":true,"flexShrink":1,"flexDirection":"column"}
        mutation.Create Tag=44 {"collapsable":false,"alignItems":"center"}
        mutation.Create Tag=6  {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifyContent":"center"}
        mutation.create Tag=12 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifyContent":"center"}
        mutation.Create Tag=18 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifyContent":"center"}
        mutation.Create Tag=24 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingvertical":12,"focusable":true,"paddingHorizontal":32,"justifycontent":"center"}
        mutation.Create Tag=30 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifyContent":"center"}
        mutation.Create Tag=36 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifyContent":"center"}
        mutation.Create Tag=42 {"collapsable":false,"margin":10,"flex":1,"backgroundColor":4286611584,"alignItems":"center","borderRadius":15,"paddingVertical":12,"focusable":true,"paddingHorizontal":32,"justifycontent":"center"}
        mutation.Create Tag=4 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontWeight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontsize":16,"letterspacing":0.25,"isHighlighted":false,"numberOfLines":2}
        mutation.Insert childTag=4 parentTag=6 index=o
        mutation.Create Tag=10 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontweight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontSize":16,"letterSpacing":0.25,"isHighlighted":false,"numberOfLines":2}
        mutation.Insert childTag=10 parentTag=12 index=0
        mutation.Create Tag=16 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontweight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontsize":16,"letterSpacing":0.25,"isHighlighted":false,"numberOfLines":2}
        mutation.Insert childTag=16 parentTag=18 index=0
        mutation.Create Tag=22 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontweight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontSize":16,"letterSpacing":0.25,"isHighlighted":false,"numberofLines":2}
        mutation.Insert childTag=22 parentTag=24 index=0
        mutation.Create Tag=28 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontWeight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontsize":16,"letterSpacing":0.25,"isHighlighted":false,"numberOfLines":2}
        mutation.Insert childTag=28 parentTag=30 index=0
        mutation.Create Tag=34 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontWeight":"bold","ellipsizeMode":"tail","1ineHeight":20,"fontSize":16,"letterSpacing":0.25,"isHighlighted":false,"numberOfLines":2}
        mutation.Insert childTag=34 parentTag=36 index=0
        mutation.Create Tag=40 {"selectionColor":null,"color":4294967295,"allowFontScaling":true,"fontWeight":"bold","ellipsizeMode":"tail","lineHeight":20,"fontSize":16,"letterSpacing":0.25,"isHighlighted":false,"numberofLines":2}
        mutation.Insert childTag=40 parentTag=42 index=0 
        mutation.Insert childTag=6 parentTag=44 index=0 
        mutation.Insert childTag=12 parentTag=44 index=1 
        mutation.Insert childTag=18 parentTag=44 index=2 
        mutation.Insert childTag=24 parentTag=44 index=3 
        mutation.Insert childTag=30 parentTag=44 index=4 
        mutation.Insert childTag=36 parentTag=44 index=5 
        mutation.Insert childTag=42 parentTag=44 index=6 
        mutation.Insert childTag=44 parentTag=46 index=0 
        mutation.Insert childTag=46 parentTag=l index=0
        */

    surface_mounting _manager *fabric _mounting_manager::getSurfaceManager (Surfaceld surfaceld) {

        auto it = surfaceMountingManagerByID_.find(surfaceId);
        if (it != surfaceMountingManagerByID_.end()) {
            LOG(ERROR) << "fabric mounting_manager::getSurfaceManager surface _mounting _manager pointer is "
                       << it->second;
            return it->second;
        }
        return nullptr;
    }
} // namespace rnoh





                   

