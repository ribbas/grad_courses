; ModuleID = 'simple-loop-unswitch.c'
source_filename = "simple-loop-unswitch.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %6 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %6) #2
  store i32 0, i32* %2, align 4, !tbaa !3
  %7 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %7) #2
  store i32 10, i32* %3, align 4, !tbaa !3
  %8 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %8) #2
  store i32 0, i32* %4, align 4, !tbaa !3
  %9 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %9) #2
  store i32 0, i32* %5, align 4, !tbaa !3
  br label %10

10:                                               ; preds = %22, %0
  %11 = load i32, i32* %2, align 4, !tbaa !3
  %12 = icmp slt i32 %11, 10
  br i1 %12, label %13, label %25

13:                                               ; preds = %10
  %14 = load i32, i32* %3, align 4, !tbaa !3
  %15 = icmp eq i32 %14, 10
  br i1 %15, label %16, label %19

16:                                               ; preds = %13
  %17 = load i32, i32* %4, align 4, !tbaa !3
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %4, align 4, !tbaa !3
  br label %22

19:                                               ; preds = %13
  %20 = load i32, i32* %5, align 4, !tbaa !3
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %5, align 4, !tbaa !3
  br label %22

22:                                               ; preds = %19, %16
  %23 = load i32, i32* %2, align 4, !tbaa !3
  %24 = add nsw i32 %23, 1
  store i32 %24, i32* %2, align 4, !tbaa !3
  br label %10, !llvm.loop !7

25:                                               ; preds = %10
  %26 = load i32, i32* %4, align 4, !tbaa !3
  %27 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %27) #2
  %28 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %28) #2
  %29 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %29) #2
  %30 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %30) #2
  ret i32 %26
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{!"clang version 13.0.1"}
!3 = !{!4, !4, i64 0}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.mustprogress"}
!9 = !{!"llvm.loop.unroll.disable"}
