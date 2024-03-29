package model1.dao;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import model1.util.DBConnect;
import model1.vo.Board;

/*
 * DataAccessObject(DAO - 데이터 접근(ex)DB접근 후, 데이터 등록, 조회, 수정, 삭제)에 관련된 작업을 하는 Class)
 * 
 * 데이터 접근에 대한 정의(ex)테이블의 생성, 수정, 삭제 / 데이터의 등록, 조회, 수정, 삭제)로직만 작성하는게 좋음
 * ex)가지고온 데이터를 가공
 */
public class BoardDAO {
//게시물 정보 조회
   public Board getBoardInfo(int boardId) {
      //게시물 vo 선언
      Board vo = null;
      
      //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      //SQL문의 결과 값을 받는 객체
      ResultSet rs = null;  // matrix형태로 받는다라고 비슷한뜻
      
      try {
           //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
           stmt = con.createStatement();  
           
           //SQL문 작성
         String sql = "   SELECT board_id, title, contents, creater, DATE_FORMAT(create_date, '%Y-%m-%d %p %h시 %i분') AS create_date, updater, DATE_FORMAT(update_date, '%Y-%m-%d %p %h시 %i분') AS update_date, read_count FROM board WHERE board_id = " + boardId;
           /*
           String sql = ""
                 + "   SELECT"
                 + "      board_id"
                 + "      , title"
                 + "      , contents"
                 + "      , creater"
                 + "      , DATE_FORMAT(create_date, '%Y-%m-%d %p %h시 %i분') AS create_date"
                 + "      , updater"
                 + "      , DATE_FORMAT(update_date, '%Y-%m-%d %p %h시 %i분') AS update_date"
                 + "      , read_count"
                 + "   FROM"
                 + "      board"
                 + "   WHERE"
                 + "      board_id = " + boardId;
           */
         System.out.println(sql);
         
         //SQL문 실행 및 결과값 반환
         rs = stmt.executeQuery(sql);
         
         //결과값이 1개의 행일 때, 데이터가 존재하는지 확인
         if (rs.next()){
             vo = new Board();
             vo.setBoardId(rs.getInt("board_id"));
             vo.setTitle(rs.getString("title"));
             vo.setContents(rs.getString("contents"));
             vo.setCreater(rs.getString("creater"));
             vo.setCreateDate(rs.getString("create_date"));
             vo.setUpdater(rs.getString("updater"));
             vo.setUpdateDate(rs.getString("update_date"));
             vo.setReadCount(rs.getInt("read_count"));
          }
         
       } catch (Exception e) {
          System.out.println("MariaDB Connection Something Problem.(MariaDB 연결에 뭔가 문제가 생긴 것 같다.)");
          System.out.println(e.getMessage());
           e.printStackTrace();
       } finally {
          //데이터 베이스 연결 종료하기
          if (con != null) {
             dbCon.disposeConn(con);
          }
       }
      
      return vo;
   }
   
   //게시물 목록 조회
   public ArrayList<Board> getBoardList() {
      //게시물 vo 선언
      Board vo = null;
      //게시물 목록을 저장할 List객체 생성 => 목록은 목록인데, 목록 내부의 행의 형태는 Board(vo) 형태, 타입을 미리 명시하여 객체의 형변환을 사용할 필요없게 함
      ArrayList<Board> arr = new ArrayList<Board>();
       
       //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      //SQL문의 결과 값을 받는 객체
      ResultSet rs = null; 
      
       try {
          //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
           stmt = con.createStatement();  
           
           //SQL문 작성
           String sql = "   SELECT board_id, title, contents, creater, DATE_FORMAT(create_date, '%Y-%m-%d %p %h시 %i분') AS create_date, updater, DATE_FORMAT(update_date, '%Y-%m-%d %p %h시 %i분') AS update_date, read_count FROM board";
           /*
           String sql = ""
                 + "   SELECT"
                 + "      board_id"
                 + "      , title"
                 + "      , contents"
                 + "      , creater"
                 + "      , DATE_FORMAT(create_date, '%Y-%m-%d %p %h시 %i분') AS create_date"
                 + "      , updater"
                 + "      , DATE_FORMAT(update_date, '%Y-%m-%d %p %h시 %i분') AS update_date"
                 + "      , read_count"
                 + "   FROM"
                 + "      board";
           */
           System.out.println(sql);
    
           //SQL문 실행 및 결과값 반환
           rs = stmt.executeQuery(sql);
          
           //결과값이 목록형태일때, 반복문을 써서 1행씩 받아옴
           while(rs.next()){
              vo = new Board();   
              vo.setBoardId(rs.getInt("board_id"));
              vo.setTitle(rs.getString("title"));
              vo.setContents(rs.getString("contents"));
              vo.setCreater(rs.getString("creater"));
              vo.setCreateDate(rs.getString("create_date"));
              vo.setUpdater(rs.getString("updater"));
              vo.setUpdateDate(rs.getString("update_date"));
              vo.setReadCount(rs.getInt("read_count"));
              
              arr.add(vo);
           }
       } catch (Exception e) {
          System.out.println("MariaDB Connection Something Problem.(MariaDB 연결에 뭔가 문제가 생긴 것 같다.)");
          System.out.println(e.getMessage());
           e.printStackTrace();
       } finally {
          //데이터 베이스 연결 종료하기
          if (con != null) {
             dbCon.disposeConn(con);
          }
       }
               
      return arr;
   }

   //게시물 등록
   public void insertBoard(Board vo) {
      //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      
      try {
         //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
         stmt = con.createStatement();
         
         //SQL문 작성
         String sql = ""
               + "   INSERT INTO board (board_id, title, contents, creater, create_date, read_count)"
               + "   VALUE ((SELECT IFNULL(MAX(b.board_id), 0) + 1 FROM board b), '" + vo.getTitle() + "', '" + vo.getContents() + "', '" + vo.getCreater() + "', NOW(), 0)";
         /*
         String sql = ""
               + "   INSERT INTO"
               + "      board ("
               + "         board_id"
               + "         , title"
               + "         , contents"
               + "         , creater"
               + "         , create_date"
               + "         , read_count"
               + "      )"
               + "   VALUE"
               + "      ("
               + "         (SELECT IFNULL(MAX(b.board_id), 0) + 1 FROM board b)"
               + "         , '" + vo.getTitle() + "'"
               + "         , '" + vo.getContents() + "'"
               + "         , '" + vo.getCreater() + "'"
               + "         , NOW()"
               + "         , 0"
               + "      )";
         */
         System.out.println(sql);
         
         //SQL문 실행
         stmt.executeQuery(sql);
      } catch (SQLException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      } finally {
          //데이터 베이스 연결 종료하기
          if (con != null) {
             dbCon.disposeConn(con);
          }
       }
   }
   
   //게시물 수정
   public void updateBoard(Board vo) {
      //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      try {
         //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
         stmt = con.createStatement();
         
         //SQL문 작성
         String sql = "   UPDATE board SET title = '" + vo.getTitle() + "', contents = '" + vo.getContents() + "', updater = '" + vo.getUpdater() + "', update_date = NOW() WHERE board_id = " + vo.getBoardId();
         /*
         String sql = ""
               + "   UPDATE"
               + "      board"
               + "   SET"
               + "      title = '" + vo.getTitle() + "'"
               + "      , contents = '" + vo.getContents() + "'"
               + "      , updater = '" + vo.getUpdater() + "'"
               + "      , update_date = NOW()"
               + "   WHERE"
               + "      board_id = " + vo.getBoardId();
         */
         System.out.println(sql);
         
         //SQL문 실행
         stmt.executeQuery(sql);
      } catch (SQLException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      }
   }
   
   //게시물 삭제
   public void deleteBoard(int boardId) {
      //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      try {
         //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
         stmt = con.createStatement();
         
         //SQL문 작성
         String sql = "   DELETE FROM board WHERE board_id = " + boardId;
         /*
         String sql = ""
               + "   DELETE"
               + "   FROM"
               + "      board"
               + "   WHERE"
               + "      board_id = " + boardId;
         */
         
         System.out.println(sql);
         
         //SQL문 실행
         stmt.executeQuery(sql);
      } catch (SQLException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      } finally {
          //데이터 베이스 연결 종료하기
          if (con != null) {
             dbCon.disposeConn(con);
          }
       }
   }

   //조회수 업데이터
   public void readCountUpdate(int boardId) {
      //데이터 베이스 연결 Class 객체 생성
      DBConnect dbCon = new DBConnect();
      
      //데이터 베이스와 연결 및 관리 해주는 객체
      Connection con = dbCon.getConnection();
      //SQL문 실행을 도와주는 객체
      Statement stmt = null;
      try {
         //SQL문 실행을 도와주는, 객체를 생성하는 메서드 호출 
         stmt = con.createStatement();
         
         //SQL문 작성
         String sql = "   UPDATE board SET read_count = read_count + 1 WHERE board_id = " + boardId;
         /*
         String sql = ""
               + "   UPDATE"
               + "      board"
               + "   SET"
               + "      read_count = read_count + 1"
               + "   WHERE"
               + "      board_id = " + boardId;
         */
         System.out.println(sql);
         
         //SQL문 실행
         stmt.executeQuery(sql);
      } catch (SQLException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      } finally {
          //데이터 베이스 연결 종료하기
          if (con != null) {
             dbCon.disposeConn(con);
          }
       }
   }
}
