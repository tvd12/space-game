package com.tvd12.space_game.request;

import com.tvd12.ezyfox.binding.annotation.EzyObjectBinding;
import com.tvd12.space_game.model.Position;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@EzyObjectBinding
public class SyncPositionRequest {
    private String gameName;
    private long gameId;
    private int objectId;
    private String objectName;
    private boolean visible;
    private Position position;
}
