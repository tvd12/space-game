package com.tvd12.space_game.entity;

import com.tvd12.ezydata.database.annotation.EzyCollection;
import com.tvd12.ezydata.database.annotation.EzyCollectionId;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@EzyCollectionId
@NoArgsConstructor
@AllArgsConstructor
public class GamePlayerId {
    private String game;
    private String player;
}
