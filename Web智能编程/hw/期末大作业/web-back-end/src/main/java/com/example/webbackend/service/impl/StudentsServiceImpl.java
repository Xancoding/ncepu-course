package com.example.webbackend.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.UpdateWrapper;
import com.example.webbackend.domain.ResponseResult;
import com.example.webbackend.entity.Students;
import com.example.webbackend.mapper.StudentsMapper;
import com.example.webbackend.service.IStudentsService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.math.BigDecimal;
import java.util.Map;

import static com.mysql.cj.util.StringUtils.isNullOrEmpty;


/**
 * <p>
 *  服务实现类
 * </p>
 *
 * @author xan
 * @since 2023-12-19
 */
@Service
public class StudentsServiceImpl extends ServiceImpl<StudentsMapper, Students> implements IStudentsService {

    @Resource
    private StudentsMapper mapper;

    @Override
    public ResponseResult getInfo(Map<String, String> params) {

        // 如果参数为空，返回所有记录
        if (params.values().stream().allMatch(String::isEmpty))
            return new ResponseResult(200, "success", mapper.selectList(null));

        // 设置查询条件
        QueryWrapper<Students> wrapper = new QueryWrapper<>();
        if (!isNullOrEmpty(params.get("studentId"))) wrapper.eq("student_id", params.get("studentId"));
        if (!isNullOrEmpty(params.get("username"))) wrapper.eq("username", params.get("username"));
        if (!isNullOrEmpty(params.get("major"))) wrapper.eq("major", params.get("major"));
        if (!isNullOrEmpty(params.get("email"))) wrapper.eq("email", params.get("email"));
        if (!isNullOrEmpty(params.get("phoneNumber"))) wrapper.eq("phone_number", params.get("phoneNumber"));
        if (!isNullOrEmpty(params.get("gender"))) wrapper.eq("gender", params.get("gender"));
        if (!isNullOrEmpty(params.get("gpa"))) wrapper.eq("gpa", params.get("gpa"));

        // 返回查询结果
        return new ResponseResult(200, "success", mapper.selectList(wrapper));
    }

    @Override
    public ResponseResult addInfo(Map<String, String> params) {

        // 如果参数为空，返回错误信息
        if (params.values().stream().allMatch(String::isEmpty)) return new ResponseResult(400, "params is empty");

        // 设置插入对象
        Students student = new Students();
        if (!isNullOrEmpty(params.get("username"))) student.setUsername(params.get("username"));
        if (!isNullOrEmpty(params.get("major"))) student.setMajor(params.get("major"));
        if (!isNullOrEmpty(params.get("email"))) student.setEmail(params.get("email"));
        if (!isNullOrEmpty(params.get("phoneNumber"))) student.setPhoneNumber(params.get("phoneNumber"));
        if (!isNullOrEmpty(params.get("gender"))) student.setGender(params.get("gender"));
        if (!isNullOrEmpty(params.get("gpa"))) student.setGpa(new BigDecimal(params.get("gpa")));

        // 插入记录
        if (mapper.insert(student) == 1) return new ResponseResult(200, "success");
        else return new ResponseResult(400, "insert failed");
    }

    @Override
    public ResponseResult deleteInfo(Map<String, String> params) {

        // 如果参数为空，返回错误信息
        if (params.values().stream().allMatch(String::isEmpty)) return new ResponseResult(400, "params is empty");

        // 设置删除条件
        QueryWrapper<Students> wrapper = new QueryWrapper<>();
        if (!isNullOrEmpty(params.get("studentId"))) wrapper.eq("student_id", params.get("studentId"));
        if (!isNullOrEmpty(params.get("username"))) wrapper.eq("username", params.get("username"));
        if (!isNullOrEmpty(params.get("major"))) wrapper.eq("major", params.get("major"));
        if (!isNullOrEmpty(params.get("email"))) wrapper.eq("email", params.get("email"));
        if (!isNullOrEmpty(params.get("phoneNumber"))) wrapper.eq("phone_number", params.get("phoneNumber"));
        if (!isNullOrEmpty(params.get("gender"))) wrapper.eq("gender", params.get("gender"));
        if (!isNullOrEmpty(params.get("gpa"))) wrapper.eq("gpa", params.get("gpa"));

        int affectedRows = mapper.delete(wrapper);

        // 删除记录
        if (affectedRows != 0) return new ResponseResult(200, "success delete " + affectedRows + " record(s)");
        else return new ResponseResult(400, "delete failed");
    }

    @Override
    public ResponseResult updateInfo(Map<String, String> params) {

        // 如果参数为空，返回错误信息
        if (params.values().stream().allMatch(String::isEmpty)) return new ResponseResult(400, "params is empty");

        // studentId为空，返回错误信息
        if (isNullOrEmpty(params.get("studentId"))) return new ResponseResult(400, "studentId is empty");

        Students student = mapper.selectById(params.get("studentId"));
        if (student == null) return new ResponseResult(400, "No matching user exists");

        // 设置更新对象
        if (!isNullOrEmpty(params.get("username"))) student.setUsername(params.get("username"));
        if (!isNullOrEmpty(params.get("major"))) student.setMajor(params.get("major"));
        if (!isNullOrEmpty(params.get("email"))) student.setEmail(params.get("email"));
        if (!isNullOrEmpty(params.get("phoneNumber"))) student.setPhoneNumber(params.get("phoneNumber"));
        if (!isNullOrEmpty(params.get("gender"))) student.setGender(params.get("gender"));
        if (!isNullOrEmpty(params.get("gpa"))) student.setGpa(new BigDecimal(params.get("gpa")));

        // 更新信息
        UpdateWrapper<Students> updateWrapper = new UpdateWrapper<>();
        updateWrapper.eq("student_id", params.get("studentId")); // 根据主键更新

        // 更新记录
        if (mapper.update(student, updateWrapper) == 1) return new ResponseResult(200, "success");
        else return new ResponseResult(400, "update failed");
    }
}
