import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class Boule {

    int x;
    int y;
    int speed;
    Color color;

    public Boule(int x, int y, Color color) {
        this.x = x;
        this.y = y;
        this.color = color;
        this.speed = 4;
    }

    public void show(GraphicsContext gc)
    {
        gc.setFill(color);
        gc.fillOval(x, y, 50, 50);
    }

    public void moveLeft() {
        if (this.x < -50)
            this.x = 512;
        this.x -= speed;
    }

    public void moveRight() {
        if (this.x > 512)
            this.x = 0;
        this.x += speed;
    }

    public void moveUp() {
        if (this.y < -50)
            this.y = 512;
        this.y -= speed;
    }

    public void moveDown() {
        if (this.y > 512)
            this.y = 0;
        this.y += speed;
    }
}
