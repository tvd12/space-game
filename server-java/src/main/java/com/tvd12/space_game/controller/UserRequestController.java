package com.tvd12.space_game.controller;

import com.tvd12.ezydata.database.repository.EzyMaxIdRepository;
import com.tvd12.ezyfox.bean.annotation.EzyAutoBind;
import com.tvd12.ezyfox.bean.annotation.EzySingleton;
import com.tvd12.ezyfox.core.annotation.EzyClientRequestController;
import com.tvd12.ezyfox.core.annotation.EzyRequestHandle;
import com.tvd12.ezyfox.util.EzyLoggable;
import com.tvd12.ezyfoxserver.entity.EzyUser;
import com.tvd12.ezyfoxserver.support.factory.EzyResponseFactory;
import com.tvd12.space_game.entity.*;
import com.tvd12.space_game.repo.GameCurrentStateRepo;
import com.tvd12.space_game.repo.GameObjectPositionRepo;
import com.tvd12.space_game.repo.LeaderBoardRepo;
import com.tvd12.space_game.repo.PlayerCurrentGameRepo;
import com.tvd12.space_game.request.*;
import com.tvd12.space_game.response.ReconnectResponse;
import lombok.Setter;

import java.util.List;

@Setter
@EzySingleton
@EzyClientRequestController
public class UserRequestController extends EzyLoggable {

    @EzyAutoBind
    private EzyResponseFactory appResponseFactory;

    @EzyAutoBind
    private GameObjectPositionRepo gameObjectPositionRepo;

    @EzyAutoBind
    private PlayerCurrentGameRepo playerCurrentGameRepo;

    @EzyAutoBind
    private GameCurrentStateRepo gameCurrentStateRepo;

    @EzyAutoBind
    private LeaderBoardRepo leaderBoardRepo;

    @EzyAutoBind
    private EzyMaxIdRepository maxIdRepository;

    @EzyRequestHandle("getGameId")
    public void getGameId(GetGameIdRequest request, EzyUser user) {
        long gameId = maxIdRepository.incrementAndGet(request.getGameName());
        PlayerCurrentGame playerCurrentGame = new PlayerCurrentGame(
                new GamePlayerId(
                        request.getGameName(),
                        user.getName()
                ),
                gameId
        );
        playerCurrentGameRepo.save(playerCurrentGame);
        appResponseFactory.newObjectResponse()
                .command("getGameId")
                .param("gameId", gameId)
                .user(user)
                .execute();
    }

    @EzyRequestHandle("startGame")
    public void startGame(StartGameRequest request, EzyUser user) {
        gameObjectPositionRepo.deleteByGameAndGameId(
                request.getGameName(),
                request.getGameId()
        );
        GameId gameId = new GameId(request.getGameName(), request.getGameId());
        GameCurrentState gameCurrentState = gameCurrentStateRepo.findById(gameId);
        if(gameCurrentState == null) {
            gameCurrentState = new GameCurrentState(gameId, GameState.PLAYING);
        }
        gameCurrentState.setState(GameState.PLAYING);
        gameCurrentStateRepo.save(gameCurrentState);
        appResponseFactory.newObjectResponse()
                .command("startGame")
                .param("gameId", gameId.getGameId())
                .user(user)
                .execute();
    }

    @EzyRequestHandle("reconnect")
    public void reconnect(ReconnectRequest request, EzyUser user) {
        String game = request.getGameName();
        String player = user.getName();
        GamePlayerId gamePlayerId = new GamePlayerId(game, player);
        ReconnectResponse response = new ReconnectResponse();
        PlayerCurrentGame playerCurrentGame = playerCurrentGameRepo.findById(gamePlayerId);
        if(playerCurrentGame != null) {
            long gameId = playerCurrentGame.getCurrentGameId();
            response.setGameId(gameId);
            GameCurrentState state =
                    gameCurrentStateRepo.findById(new GameId(game, gameId));
            response.setGameState(state != null ? state.getState() : GameState.FINISHED);
            LeaderBoard leaderBoard =
                    leaderBoardRepo.findById(new LeaderBoard.Id(game, gameId, player));
            response.setPlayerScore(leaderBoard != null ? leaderBoard.getScore() : 0L);
            List<GameObjectPosition> gameObjectPositions =
                    gameObjectPositionRepo.findByGameAndGameId(game, gameId);
            for(GameObjectPosition gameObjectPosition: gameObjectPositions) {
                response.addGameObject(new ReconnectResponse.GameObject(
                    gameObjectPosition.getId().getObjectId(),
                    gameObjectPosition.getObjectName(),
                    gameObjectPosition.isVisible(),
                    gameObjectPosition.getPosition()
                ));
            }
        }
        appResponseFactory.newObjectResponse()
                .command("reconnect")
                .user(user)
                .data(response)
                .execute();
    }

    @EzyRequestHandle("syncPosition")
    public void syncPosition(SyncPositionRequest request, EzyUser user) {
        GameObjectPosition gameObjectPosition = new GameObjectPosition(
                new GameObjectPosition.Id(
                        request.getGameName(),
                        request.getGameId(),
                        request.getObjectId()
                ),
                user.getName(),
                request.getObjectName(),
                request.isVisible(),
                request.getPosition()
        );
        gameObjectPositionRepo.save(gameObjectPosition);
    }

    @EzyRequestHandle("updateScore")
    public void updateScore(UpdateScoreRequest request, EzyUser user) {
        LeaderBoard leaderBoard = new LeaderBoard(
                new LeaderBoard.Id(
                        request.getGameName(),
                        request.getGameId(),
                        user.getName()
                ),
                request.getScore()
        );
        leaderBoardRepo.save(leaderBoard);
    }

}
