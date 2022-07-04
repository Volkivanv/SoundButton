#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaPlaylist>

class ImageButton: public QPushButton
{
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;
};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("Stop");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("ButtonUn.png");
    mButtonDownPixmap = QPixmap("ButtonPush.png");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    connect(this,&QPushButton::clicked, this, &ImageButton::setDown);
}
void ImageButton::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);

}
QSize ImageButton::sizeHint() const {
    return QSize(100,100);
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}
void ImageButton::setDown() {
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100,this, &ImageButton::setUp);
}
void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWidget soundButtonWindow;
    soundButtonWindow.setFixedSize(100,100);
    ImageButton redButton(&soundButtonWindow);
    redButton.setFixedSize(100,100);
    redButton.move(0,0);
    QString filePath = "elButtonSound.mp3";
    auto *player = new QMediaPlayer(&soundButtonWindow);
    QObject::connect(&redButton,&QPushButton::clicked,[&filePath, player](){
        player->setMedia((QUrl::fromLocalFile(filePath)));
        player->setVolume(75);
        player->play();
    });
    soundButtonWindow.show();
    return QApplication::exec();
}
