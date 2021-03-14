package com.tvd12.space_game.controller;

import com.tvd12.ezyfox.bean.annotation.EzyAutoBind;
import com.tvd12.ezyfox.bean.annotation.EzySingleton;
import com.tvd12.ezyfox.core.annotation.EzyClientRequestController;
import com.tvd12.ezyfox.core.annotation.EzyRequestHandle;
import com.tvd12.ezyfox.util.EzyLoggable;
import com.tvd12.ezyfoxserver.entity.EzyUser;
import com.tvd12.ezyfoxserver.support.factory.EzyResponseFactory;
import com.tvd12.space_game.entity.GameObjectPosition;
import com.tvd12.space_game.repo.GameObjectPositionRepo;
import com.tvd12.space_game.request.SyncPositionRequest;
import lombok.Setter;

@Setter
@EzySingleton
@EzyClientRequestController
public class UserRequestController extends EzyLoggable {

    @EzyAutoBind
    protected EzyResponseFactory appResponseFactory;

    @EzyAutoBind
    protected GameObjectPositionRepo gameObjectPositionRepo;

    @EzyRequestHandle("syncPosition")
    public void syncPosition(SyncPositionRequest request, EzyUser user) {
        GameObjectPosition entity = new GameObjectPosition(
                new GameObjectPosition.Id(
                        request.getGameName(),
                        user.getName(),
                        request.getObjectName(),
                        request.getObjectIndex()
                ),
                request.getPosition()
        );
        gameObjectPositionRepo.save(entity);
    }
}
