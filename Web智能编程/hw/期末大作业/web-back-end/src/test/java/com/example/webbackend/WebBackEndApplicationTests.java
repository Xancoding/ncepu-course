package com.example.webbackend;

import com.baomidou.mybatisplus.generator.FastAutoGenerator;
import com.baomidou.mybatisplus.generator.config.DataSourceConfig;
import org.apache.ibatis.annotations.Mapper;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;
import javax.sql.DataSource;

@SpringBootTest
class DemoApplicationTests {

    @Resource
    DataSource source;

//    @Test
    void contextLoads() {
        FastAutoGenerator
                .create(new DataSourceConfig.Builder(source))
                .globalConfig(builder -> {
                    builder.author("xan");              //作者信息，一会会变成注释
                    builder.outputDir("src\\main\\java"); //输出目录设置为当前项目的目录
                })
                //打包设置，这里设置一下包名就行，注意跟我们项目包名设置为一致的
                .packageConfig(builder -> builder.parent("com.example.webbackend"))
                .strategyConfig(builder -> {
                    //设置为所有Mapper添加@Mapper注解
                    builder
                            .entityBuilder()
                            .fileOverride()
                            .mapperBuilder()
                            .mapperAnnotation(Mapper.class)
                            .build();
                })
                .execute();
    }
}

