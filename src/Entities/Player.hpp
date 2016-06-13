#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QSound>
#include <memory>
#include "QBox2D/QBody.hpp"
#include "Utility/Path.hpp"

class Bullet : public QBody {
 private:
  QPointF m_direction;
  std::shared_ptr<QSound> m_punchSound;

  void onStepped();

 protected:
  void beginContact(QFixture* other, b2Contact*);

 public:
  using QBody::QBody;

  void initialize(QWorld*);
  void setDirection(QPointF);
  void setSound(std::shared_ptr<QSound>);
};

class Player : public QBody {
 private:
  QPointF m_target;
  std::unique_ptr<Path> m_currentPath;
  size_t m_currentPathPoint;
  bool m_going;
  std::string m_activeSpell;
  std::shared_ptr<QSound> m_punchSound;

  void onStepped();

 protected:
  void mousePressEvent(QMouseEvent*);
  void keyPressEvent(QKeyEvent*);

 public:
  Player(SceneGraph::Item* = nullptr);

  void initialize(QWorld* w);

  bool write(QJsonObject&) const;

  void move(QPointF);
  void setActiveSpell(std::string str);
  const std::string& activeSpell() const;
  void castSpell(const QPointF& position, int spellId);
};

#endif  // PLAYER_HPP
