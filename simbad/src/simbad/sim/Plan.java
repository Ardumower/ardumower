/* author: Louis Hugues - created on 21 janv. 2005  */
package simbad.sim;

import java.util.ArrayList;

/**
 *  
 */
public class Plan {
    Agent agent;
    ArrayList actions;
    int state, count;

    private class Transition {

        int nextState, steps;
        Transition(int steps, int nextState) {
            this.nextState = nextState;
            this.steps = steps;
        }

        void doStep() { }
    }

    private class Movement extends Transition {

        double rvel, tvel;

        Movement(double t, double r, int steps, int nextState) {
            super(steps, nextState);
            tvel = t;
            rvel = r;
        }

        void doStep() {
            agent.setTranslationalVelocity(tvel);
            agent.setRotationalVelocity(rvel);
        }
    }

    public Plan(Agent agent) {
        this.agent = agent;
        actions = new ArrayList();
        state = 0;
        count = 0;
    }

    public void reset() {
        state = 0;
        Transition t = (Transition) actions.get(state);
        count = t.steps;
       }

    public void turn(double angle, double duration) {
        float fps=20; //TODO 
        actions.add(new Movement(0,angle/duration,(int)(duration*fps), actions.size()+1));
    }

    public void forward(double distance, double duration) {
        float fps=20; //TODO 
        actions.add(new Movement(distance/duration,0,(int)(duration*fps), actions.size()+1));
    }

    public void loop() {
        ((Transition) actions.get(actions.size()-1)).nextState = 0;
    }

    public void doStep() {
        if ((state>=actions.size())|| (count <=0)) return;
        Transition t = (Transition) actions.get(state);
        t.doStep();
        count--;
        if (count == 0) {
            state = t.nextState;
            count = t.steps;
        }
    }
}