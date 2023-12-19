package com.example.webbackend.service;

import com.example.webbackend.domain.ResponseResult;
import com.example.webbackend.entity.Students;
import com.baomidou.mybatisplus.extension.service.IService;

import java.util.Map;

/**
 * <p>
 *  服务类
 * </p>
 *
 * @author xan
 * @since 2023-12-19
 */
public interface IStudentsService extends IService<Students> {
    ResponseResult getInfo(Map<String, String> params);

    ResponseResult addInfo(Map<String, String> params);

    ResponseResult deleteInfo(Map<String, String> params);

    ResponseResult updateInfo(Map<String, String> params);
}
