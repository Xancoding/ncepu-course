<template>
  <Layout>
    <el-table :data="tableData" style="width: 100%">
      <el-table-column prop="studentId" label="studentId" />
      <el-table-column prop="username" label="username" />
      <el-table-column prop="major" label="major" />
      <el-table-column prop="email" label="email" />
      <el-table-column prop="phoneNumber" label="phoneNumber" />
      <el-table-column prop="gender" label="gender" />
      <el-table-column prop="gpa" label="gpa">
        <template v-slot="scope">
          <div style="display: flex; align-items: center;">
            <span v-if="scope.row.gpa">{{ scope.row.gpa }}</span>
            <el-button @click="handleDelete(scope.row)" type="danger" style="margin-left: auto;">Delete</el-button>
          </div>
        </template>
      </el-table-column>
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
  name: 'Delete',

  created () {
    // 进入页面就加载
    this.getAllInfo()
  },

  data () {
    return {
      tableData: [],
    }
  },

  methods: {
    async getAllInfo () {
      const res = await axios({
        url: 'http://localhost:8888/students/getInfo',
        method: 'GET',
        params: {
          studentId: null,
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

    async handleDelete (row) {
      this.$confirm(`确定删除吗？`, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
      }).then(async () => {
        const res = await axios({
          url: 'http://localhost:8888/students/deleteInfo',
          method: 'POST',
          params: {
            studentId: row.studentId,
          }
        })

        if (res.data.code === 200) {
          this.$message({
            message: res.data.msg,
            type: 'success'
          })
        } else {
          this.$message({
            message: res.data.msg,
            type: 'error'
          })
        }
        this.getAllInfo()
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除',
        });
      });
    },
  }
};
</script>