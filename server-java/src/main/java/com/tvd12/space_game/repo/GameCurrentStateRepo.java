package com.tvd12.space_game.repo;

import com.tvd12.ezydata.mongodb.EzyMongoRepository;
import com.tvd12.ezyfox.database.annotation.EzyRepository;
import com.tvd12.space_game.entity.GameCurrentState;
import com.tvd12.space_game.entity.GameId;

@EzyRepository
public interface GameCurrentStateRepo
        extends EzyMongoRepository<GameId, GameCurrentState> {
}
