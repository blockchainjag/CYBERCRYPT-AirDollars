public class TotalIssuance{
    public static void main(String[]args) {
        double total = 0;
        int block = 0;
        double reward = 50.0;

        while(reward >= 0.00000001){
            total += reward;
            block++;

            if(block % 210000 == 0){
                reward /= 2;
            }
        }

        System.out.println("blocks=" + block);
        System.out.println("total=" + total);
    }
}