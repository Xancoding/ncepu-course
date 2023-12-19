package com.example.webbackend.controller;

import com.example.webbackend.domain.ResponseResult;
import com.example.webbackend.service.IStudentsService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.Map;

/**
 * <p>
 *  前端控制器
 * </p>
 *
 * @author xan
 * @since 2023-12-19
 */
@RestController
@RequestMapping("/students")
@CrossOrigin(origins = "*") // 放在类级别，为整个Controller指定默认CORS配置
public class StudentsController {

    @Autowired
    private IStudentsService studentsService;

    @GetMapping("/getInfo")
    public ResponseResult getInfo(@RequestParam Map<String, String> params)
    {
        return studentsService.getInfo(params);
    }

    @PostMapping("/insertInfo")
    public ResponseResult addInfo(@RequestParam Map<String, String> params) {
        return studentsService.addInfo(params);
    }

    @PostMapping("/deleteInfo")
    public ResponseResult deleteInfo(@RequestParam Map<String, String> params) {
        return studentsService.deleteInfo(params);
    }

    @PostMapping("/updateInfo")
    public ResponseResult updateInfo(@RequestParam Map<String, String> params) {
        return studentsService.updateInfo(params);
    }
}
