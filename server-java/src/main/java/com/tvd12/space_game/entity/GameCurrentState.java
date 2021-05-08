package com.tvd12.space_game.entity;

import com.tvd12.ezyfox.annotation.EzyId;
import com.tvd12.ezyfox.database.annotation.EzyCollection;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@EzyCollection
@NoArgsConstructor
@AllArgsConstructor
public class GameCurrentState {
    @EzyId
    private GameId id;
    private GameState state;
}
