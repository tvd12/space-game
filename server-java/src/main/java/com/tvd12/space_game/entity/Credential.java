package com.tvd12.space_game.entity;

import com.tvd12.ezydata.database.annotation.EzyCollection;
import com.tvd12.ezyfox.annotation.EzyId;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@EzyCollection
@NoArgsConstructor
@AllArgsConstructor
public class Credential {
    @EzyId
    private GamePlayerId id;
    private String password;
}
