
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import Models.RVBModel;
import static org.junit.Assert.*;

/**
 *
 * @author laubosslink <laubosslink@society-lbl.com>
 */
public class TestRVB {
    RVBModel rvb;
    
    public TestRVB() {
    }

    @BeforeClass
    public static void setUpClass() throws Exception {
    }

    @AfterClass
    public static void tearDownClass() throws Exception {
    }
    
    @Before
    public void setUp() {
        rvb = new RVBModel(67, 22, 11);
    }
    
    @After
    public void tearDown() {
    }
    
    @Test(expected=IllegalArgumentException.class)
    public void TestConstructor(){
        new RVBModel(67, 10, 11);
    }
    
    @Test
    public void TestValues(){
        int total = rvb.getB() + rvb.getR() + rvb.getV();
        assertEquals(total, 100);
    }
    
    @Test
    public void TestBalance(){
        int total = 0;
        
        rvb.setV(54);
        total = rvb.getB() + rvb.getR() + rvb.getV();
        assertEquals(total, 100);
        
        rvb.setR(88);
        total = rvb.getB() + rvb.getR() + rvb.getV();
        assertEquals(total, 100);
        
        for(int i=0; i<=100; i++){
            rvb.setB(i);
            total = rvb.getB() + rvb.getR() + rvb.getV();
            assertEquals(total, 100);
        }
    }
}
