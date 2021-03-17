package com.tvd12.space_game.request;

import com.tvd12.ezyfox.binding.annotation.EzyObjectBinding;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@EzyObjectBinding
public class UpdateScoreRequest {
    private String gameName;
    private long gameId;
    private long score;
}
