// 切换背景颜色
const colors = ['#FFF5C2', '#F4F27E', '#6DB9EF']; // 你可以添加更多颜色

document.addEventListener('DOMContentLoaded', function() {
  const changeColorBtn = document.getElementById('changeColorBtn');
  const contentDiv = document.getElementById('contentDiv');

  changeColorBtn.addEventListener('click', function() {
    const randomIndex = Math.floor(Math.random() * colors.length);
    const selectedColor = colors[randomIndex];
    contentDiv.style.backgroundColor = selectedColor;
  });
});

