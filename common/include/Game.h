#pragma once
#include "Input.h"
#include "Metrics.h"
#include "World.h"

class Rollback;

enum class BallType {
  kFootball = 0,
  kBasketball,
  kBaseball,
  kVolleyball,
  kTennisball,
  kCount
};

enum class GameState { kMenu, kInGame, kGameFinished };

/**
 * \brief Handles the physics state of the app
 */
class Game : public ContactListener {
 private:
  World world_;

  GameState state_ = GameState::kMenu;

  input::Input input_{};
  input::Input other_player_input_{};

  std::vector<BodyRef> body_refs_;
  std::vector<ColliderRef> col_refs_;

  ColliderRef ground_col_ref_{};

  // Represents a reference to the blue player's body in the physics engine.
  BodyRef player_blue_body_ref_{};

  // Represents a reference to the blue player's main collision shape.
  ColliderRef player_blue_col_ref_{};

  // Represents a reference to the blue player's feet collision shape,
  // used for kicking the ball.
  ColliderRef player_blue_feet_col_ref_{};

  // Indicates whether the blue player is currently on the ground.
  bool is_player_blue_grounded_ = false;

  // A timer tracking the time elapsed since the blue player last kicked the
  // ball, initially set to 1 second so the player can kick from the start.
  float player_blue_kick_time_ = 1.f;

  // A flag indicating whether the blue player can currently kick the ball
  bool can_player_blue_kick_ = false;

  // Keeps track of the blue player's score in the game; initially set to zero.
  int blue_score_ = 0;

  ColliderRef player_red_col_ref_{};

  ColliderRef player_red_feet_col_ref_{};

  float player_red_kick_time_ = 1.f;

  bool can_player_red_kick_ = false;

  // represents the type of the ball, it changes it's bouciness and mass so the
  // game is less repetitive, not fully implemented yet
  BallType ball_type_ = BallType::kFootball;

  // Represents a reference to the ball's body in the physics engine.
  BodyRef ball_body_ref_{};

  // Represents a reference to the ball's main collision shape.
  ColliderRef ball_col_ref_{};

  // Represents the radius of ball, it changes depending on the BallType,
  //  not fully implemented yet
  float ball_radius_ = metrics::kBallRadiusMedium;

  int red_score_ = 0;

  ColliderRef left_goal_col_ref_{};
  ColliderRef right_goal_col_ref_{};
  BodyRef player_red_body_ref_{};

  bool is_player_red_grounded_ = false;

  static constexpr float kBallGravity = 1000;
  static constexpr float kPlayerGravity = 2500;
  static constexpr float kWalkSpeed = 1500;
  static constexpr float kMaxSpeed = 1200;
  static constexpr float kJumpSpeed = -75000;
  static constexpr float kPlayerMass = 5;

  static constexpr float kShootForce = 25000;

 public:
  int player_nbr = -1;

  void Copy(const Game& other);

  void Setup() noexcept;
  void Update() noexcept;
  void FixedUpdate() noexcept;
  void TearDown() noexcept;

  void StartGame();
  GameState GetState();

  float GetBallRadius() const noexcept;
  Math::Vec2F GetBallPosition() noexcept;
  Math::Vec2F GetBallVelocity() noexcept;
  BallType GetBallType() noexcept;

  int GetBlueScore() noexcept { return blue_score_; }
  int GetRedScore() noexcept { return red_score_; }

  Math::Vec2F GetPlayerBluePos() noexcept;
  Math::Vec2F GetPlayerRedPos() noexcept;

  void SetPlayerInput(input::Input input) noexcept;
  void SetOtherPlayerInput(input::Input input) noexcept;

  void SetBallType(BallType type) noexcept { ball_type_ = type; }

  void EndGame();
  void Restart();

  void OnTriggerEnter(ColliderRef col1, ColliderRef col2) noexcept override;

  void OnTriggerExit(ColliderRef col1, ColliderRef col2) noexcept override;

  void OnCollisionEnter(ColliderRef col1, ColliderRef col2) noexcept override;

  void OnCollisionExit(ColliderRef col1, ColliderRef col2) noexcept override {}

  int CheckSum() noexcept;

 private:
  void ProcessInput() noexcept;
  void ResetPositions() noexcept;

  void CreateBall() noexcept;
  void CreateTerrain() noexcept;
  void CreatePlayers() noexcept;
};