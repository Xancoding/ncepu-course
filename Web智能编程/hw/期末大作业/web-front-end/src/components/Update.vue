<template>
  <Layout>
    <el-table :data="tableData" style="width: 100%">
      <el-table-column :prop="column.prop" :label="column.label" v-for="(column, index) in columns" :key="column.prop">
        <template v-slot="scope">
          <div style="display: flex; align-items: center;">
            <el-input v-model="scope.row[column.prop]" :disabled="index === 0"></el-input>
          </div>
        </template>
      </el-table-column>
      <el-table-column>
        <template v-slot="scope">
          <el-button @click="handleUpdate(scope.row)" type="warning" style="margin-left: auto;">Update</el-button>
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
  name: 'Update',

  created () {
    // 进入页面就加载
    this.getAllInfo()
  },

  data () {
    return {
      tableData: [],
      columns: [
        { prop: 'studentId', label: 'studentId' },
        { prop: 'username', label: 'username' },
        { prop: 'major', label: 'major' },
        { prop: 'email', label: 'email' },
        { prop: 'phoneNumber', label: 'phoneNumber' },
        { prop: 'gender', label: 'gender' },
        { prop: 'gpa', label: 'gpa' },
      ],
    };
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

    async handleUpdate (row) {
      this.$confirm(`确定更新吗？`, '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
      }).then(async () => {
        const res = await axios({
          url: 'http://localhost:8888/students/updateInfo',
          method: 'POST',
          params: {
            studentId: row.studentId,
            username: row.username,
            major: row.major,
            email: row.email,
            phoneNumber: row.phoneNumber,
            gender: row.gender,
            gpa: row.gpa
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
          message: '已取消更新',
        });
      });
    }
  }

};

</script>