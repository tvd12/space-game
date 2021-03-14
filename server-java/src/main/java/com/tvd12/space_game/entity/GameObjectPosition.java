package com.tvd12.space_game.entity;

import com.tvd12.ezydata.database.annotation.EzyCollection;
import com.tvd12.ezydata.database.annotation.EzyCollectionId;
import com.tvd12.space_game.model.Position;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@EzyCollection
@NoArgsConstructor
@AllArgsConstructor
public class GameObjectPosition {
    @EzyCollectionId(composite = true)
    private Id id;
    private Position position;

    @Getter
    @Setter
    @NoArgsConstructor
    @AllArgsConstructor
    public static class Id {
        private String game;
        private String player;
        private String objectName;
        private int index;
    }
}
