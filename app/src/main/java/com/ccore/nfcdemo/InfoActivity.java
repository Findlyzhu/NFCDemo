package com.ccore.nfcdemo;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class InfoActivity extends AppCompatActivity {
    private List<Info> infoList = new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_info);
        InfoAdapter adapter = new InfoAdapter(getApplicationContext(),R.layout.info_item,infoList);
        Intent i =getIntent();
        ListView listView = (ListView) findViewById(R.id.info);
        listView.setAdapter(adapter);
        Info info2 = new Info("生产厂商:",i.getStringExtra("生产厂商"));
        Info info3 = new Info("产品SN号:",i.getStringExtra("产品SN号"));
        //infoList.add(info1);
        infoList.add(info2);
        infoList.add(info3);
    }
}
