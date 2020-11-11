import java.util.ArrayList;

import javax.swing.Action;

import javafx.animation.AnimationTimer;
import javafx.animation.TranslateTransition;
import javafx.application.Application;
import javafx.css.Declaration;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.util.Duration;

public class Main extends Application {

    Scene scene1, scene2;
    int x, y;

    public static void main(String[] args) {
        launch(args);
    }

    /*@Override
    public void start(Stage primaryStage) throws Exception {
        // Layout 1
        VBox layout1 = new VBox();
        Label label1 = new Label("Bienvenue");
        Button button1 = new Button("Aller à la page 2");
        scene1 = new Scene(layout1, 300, 300);
        button1.setOnAction(e -> primaryStage.setScene(scene2));
        layout1.getChildren().addAll(label1, button1);

        // Test
        Canvas canvas = new Canvas(500, 500);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        gc.setFill(Color.RED);
        gc.strokeLine(0, 0, 500, 500);
        VBox layout2 = new VBox();
        Button button2 = new Button("Aller à la page 1");
        button2.setOnAction(e -> primaryStage.setScene(scene1));
        layout2.getChildren().addAll(canvas, button2);
        scene2 = new Scene(layout2);
        
        primaryStage.setScene(scene1);
        primaryStage.setTitle("Test JavaFX");
        primaryStage.show();
    }*/
    @Override
    public void start(Stage theStage)
    {
        theStage.setTitle("Test JavaFX");

        Group root = new Group();
        Scene theScene = new Scene(root);
        theStage.setScene(theScene);
        Boule player = new Boule(0, 0, Color.MAGENTA);
        Canvas canvas = new Canvas(512, 512);
        root.getChildren().add(canvas);
        ArrayList<String> input = new ArrayList<String>();
        
 
        theScene.setOnKeyPressed(
            new EventHandler<KeyEvent>()
            {
                public void handle(KeyEvent e)
                {
                    String code = e.getCode().toString();
 
                    // only add once... prevent duplicates
                    if ( !input.contains(code) )
                        input.add( code );
                }
            });
 
        theScene.setOnKeyReleased(
            new EventHandler<KeyEvent>()
            {
                public void handle(KeyEvent e)
                {
                    String code = e.getCode().toString();
                    input.remove( code );
                }
            });

        new AnimationTimer()
        {
            @Override
            public void handle(long currentNanoTime)
            {
                GraphicsContext gc = canvas.getGraphicsContext2D();
                
                if (input.contains("LEFT"))
                    player.moveLeft();
                if (input.contains("RIGHT"))
                    player.moveRight();
                if (input.contains("UP"))
                    player.moveUp();
                if (input.contains("DOWN"))
                    player.moveDown();

                gc.setFill(Color.BLACK);
                gc.fillRect(0, 0, 512, 512);;
                player.show(gc);
            }
        }.start();

        theStage.show();
    }
}