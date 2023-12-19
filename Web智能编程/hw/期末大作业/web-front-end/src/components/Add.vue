<template>
  <Layout>
    <el-form :inline="true">
      <el-form-item label="username">
        <el-input v-model="username" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item label="major">
        <el-input v-model="major" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item label="email">
        <el-input v-model="email" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item label="phoneNumber">
        <el-input v-model="phoneNumber" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item label="gender">
        <el-input v-model="gender" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item label="gpa">
        <el-input v-model="gpa" placeholder="可以为空" clearable size="small"/>
      </el-form-item>
      <el-form-item>
        <el-button type="success" @click="insert" size="small">Insert</el-button>
      </el-form-item>
    </el-form>

    <el-table :data="tableData" style="width: 100%">
      <el-table-column prop="studentId" label="studentId" />
      <el-table-column prop="username" label="username" />
      <el-table-column prop="major" label="major" />
      <el-table-column prop="email" label="email" />
      <el-table-column prop="phoneNumber" label="phoneNumber" />
      <el-table-column prop="gender" label="gender" />
      <el-table-column prop="gpa" label="gpa" />
    </el-table>
  </Layout>
</template>

<script>
import Layout from '@/components/Layout.vue';
import axios from 'axios';

export default {
  components: {
    Layout,
  },
  name: 'Add',

  created () {
    // 进入页面就加载
    this.getAllInfo()
  },

  data () {
    return {
      tableData: [],
      studentId: null,
      username: null,
      major: null,
      email: null,
      phoneNumber: null,
      gender: null,
      gpa: null
    }
  },

  methods: {
    async getAllInfo () {
      const res = await axios({
        url: 'http://localhost:8888/students/getInfo',
        method: 'GET',
        params: {
          username: null,
          major: null,
          email: null,
          phoneNumber: null,
          gender: null,
          gpa: null
        }
      })
      this.tableData = res.data.data
    },

    async insert () {
      const res = await axios({
        url: 'http://localhost:8888/students/insertInfo',
        method: 'POST',
        params: {
          username: this.username,
          major: this.major,
          email: this.email,
          phoneNumber: this.phoneNumber,
          gender: this.gender,
          gpa: this.gpa
        }
      })

      if (res.data.code === 200) {
        this.$message({
          message: 'Insert successfully',
          type: 'success'
        })
      } else {
        this.$message({
          message: res.data.msg,
          type: 'error'
        })
      }


      this.getAllInfo()
    }

  }
};
</script>