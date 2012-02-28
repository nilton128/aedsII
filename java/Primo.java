/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package primo;

/**
 *
 * @author Nilton
 */
import javax.swing.JOptionPane;
public class Primo {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        int p,i,num;
        p=1;
        i=2;
        num=Integer.parseInt(JOptionPane.showInputDialog("Digite .:"));
        while(i<num) {
           if(num%i==0)
              p=0;
           i++;
        }
        if (p==1 && num>1)
           JOptionPane.showMessageDialog(null,"Numero primo ");
        else
           JOptionPane.showMessageDialog(null,"Numero nao primo ");
    }
}
