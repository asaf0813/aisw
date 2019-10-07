package model1.util;

import java.sql.Connection; 
import java.sql.DriverManager;
import java.sql.SQLException;

public class DBConnect {
   //데이터 베이스와 연결 및 관리 해주는 class(객체)
   Connection conn;
   //String url = "jdbc:oracle:thin:@localhost:1521:xe";//오라클.ver
   String url = "jdbc:mariadb://localhost:3306/edu";//mariadb.ver
   String userid = "edu";//DBMS접속 ID
   String passwd = "1234";//DBMS접속 PW
     
   public Connection getConnection() {//연결 메서드
      System.out.println("url:::"+url);//Consol에서 확인하기 위해 사용
      System.out.println("userid:::"+userid);//Consol에서 확인하기 위해 사용
      System.out.println("passwd:::"+passwd);//Consol에서 확인하기 위해 사용
       try {
          //Class.forName("oracle.jdbc.driver.OracleDriver");//오라클.ver (우리가 추가한 jdbc에서 oracle driver을 실행시키는것)
          Class.forName("org.mariadb.jdbc.Driver");//mariadb.ver
          conn = DriverManager.getConnection(url,userid,passwd);//DB연결을 위한 URL, DB접속을 위한 ID와 PW를 담아줌
          System.out.println("MariaDB 서버에 연결 성공");//Consol에서 확인하기 위해 사용
       } catch(SQLException e1) {//오류발생시
          System.out.println(e1 + " : 연결 실패");//Consol에서 확인하기 위해 사용
       } catch(ClassNotFoundException e2) {//오류발생시
          System.out.println(e2 + " : 드라이버 로딩 실패?");//Consol에서 확인하기 위해 사용
       }
       return conn;
   }
   public void disposeConn(Connection conn) {//연결 해제 메서드
      try {
         conn.close();//작업이 끝나고 나면 반드시 닫아주어야 한다. 그렇지 않으면 서버의 리소스를 계속 낭비하는 문제가 발생
         System.out.println("오라클 서버에 연결 해제");//Consol에서 확인하기 위해 사용
      }
      catch (SQLException e) {//오류 발생시
         e.printStackTrace();//에러 메세지의 발생 근원지를 찾아서 단계별로 에러를 출력
      }
   }
}